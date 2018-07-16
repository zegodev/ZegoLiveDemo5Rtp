package com.zego.livedemo5.ui.activities.wolvesgame;

import android.content.Context;
import android.content.Intent;
import android.graphics.Rect;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.zego.livedemo5.R;
import com.zego.livedemo5.ZegoApiManager;
import com.zego.livedemo5.ui.activities.LogListActivity;
import com.zego.livedemo5.ui.activities.base.AbsBaseLiveActivity;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.livedemo5.utils.ZegoRoomUtil;
import com.zego.zegoliveroom.ZegoLiveRoom;
import com.zego.zegoliveroom.callback.IZegoCustomCommandCallback;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.constants.ZegoVideoViewMode;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;
import com.zego.zegoliveroom.entity.ZegoUser;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.LinkedList;

import butterknife.Bind;

public abstract class WolvesGameBaseActivity extends AbsBaseLiveActivity {

    static final protected String kSpeakingCommandKey = "command";

    static final protected String kSpeakingUserIdKey  = "userId";

    static final protected String kCurrentUserListKey = "currentUserList";
    static final protected String kNewUserKey         = "newUser";

    static final protected String kUserIdKey          = "userId";
    static final protected String kUserNameKey        = "userName";

    static final protected String kSpeakingModeKey    = "roomMode";
    static final protected String kUserIndexKey       = "userIndex";

    /** @see com.zego.livedemo5.ui.activities.wolvesgame.WolfInfo.SpeakingState */
    static final protected String kUserStateKey       = "speakingState";

    static final protected String kServerModeIndexKey = "urtralServer";     // true 使用自己的服务器推流，false 使用CDN（延时比较大）
    static final protected String kSuperLowDelayMode  = "dontStopPublish";  // true 极速模式: 停止说话时，不终止推流，仅关闭 Mic & Camera

    static final protected String kUserCharacterKey   = "character";

    /** 发信停止说话信令与停止推流之间的时间间隔，用于确保按停止说话按钮时，所有语音都能正常推送出去 */
    static final protected int kPostSpeakingInterval  = 2;
    /** 开始说话后，设置结束说话倒计时。即轮流模式下允许单次说话的最长时间 */
    static final protected int kSpeakingTimerInterval = 60;
    /** 轮流说话模式下，组织者（Host）用于设定某位说话者的最长时间，避免说话者异常离开导致游戏无法继续的情况 */
    static final protected int kAnchorTimerInterval   = 5 + kSpeakingTimerInterval;

    /** 轮流说话模式下，计时器相关的消息 */
    protected class MsgIds {
        static final int UPDATE_COUNT_TIMER = 0x100;            // 计时器
        static final int STOP_SPEAKING_FOR_ME = 0x101;          // 计时结束，自己停止本轮说话
        static final int NOTIFY_OTHER_STOP_SPEAKING = 0x102;    // 计时结束，主播通知他人停止本轮说话
    }

    @Bind(R.id.toolbar)
    public Toolbar toolBar;

    @Bind(R.id.small_view_container)
    public RecyclerView mJoinedUsers;

    @Bind(R.id.vl_big_view)
    public TextureView mCurrentSpeakingHead;

    @Bind(R.id.txt_current_status)
    public TextView mTextTips;


    @Bind(R.id.wolf_role)
    public TextView mTextRole;

    @Bind(R.id.wolf_timer_count)
    public TextView mTimerView;

    @Bind(R.id.btn_start_or_stop_speaking)
    public Button mBtnSpeaking;

    @Bind(R.id.in_turn_speaking)
    public TextView mInTurnSpeaking;

    @Bind(R.id.end_in_turn_speaking)
    public TextView mEndInTurnSpeaking;

    protected ZegoLiveRoom zegoLiveRoom;

    protected RecyclerGridViewAdapter mRecyclerAdapter;

    protected String roomId;
    protected String roomName = "Wolves Game";

    protected boolean isSpeaking;
    protected boolean hasLoginRoom = false;

    protected PublishMode currentPublishMode = PublishMode.Low_Delay;
    protected int currentSpeakingMode = SpeakingMode.FreeSpeakingMode;

    protected boolean dontPreviewWhenPublishSuccess = false;

    /** 进入房间的所有成员列表 */
    protected LinkedList<WolfInfo> allWolfMembers;

    private Handler.Callback mHandlerCallback = new Handler.Callback() {
        @Override
        public boolean handleMessage(Message msg) {
            return handleUIMessage(msg);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_wolves_game, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.log: {
                Intent intent = new Intent(this, LogListActivity.class);
                startActivity(intent);
            }
                return true;

            default:
                return super.onOptionsItemSelected(item);
        }
    }

    /**
     * 获取内容页面的布局.
     *
     * @return 返回内容页面的布局
     */
    @Override
    protected int getContentViewLayout() {
        return R.layout.activity_wolves_game;
    }


    /**
     * 初始化子类中的变量.
     */
    @Override
    protected void initVariables(Bundle savedInstanceState) {
        zegoLiveRoom = ZegoApiManager.getInstance().getZegoLiveRoom();
        allWolfMembers = new LinkedList<>();
        mRecyclerAdapter = new RecyclerGridViewAdapter(this);
    }

    /**
     * 初始化子类中的控件.
     */
    @Override
    protected void initViews(Bundle savedInstanceState) {
        int spanCount = 4;
        if(mJoinedUsers == null) {
            mJoinedUsers = (RecyclerView)findViewById(R.id.small_view_container);
        }

        mJoinedUsers.addItemDecoration(new GridSpacingItemDecoration(spanCount, 10, false));
        mJoinedUsers.setAdapter(mRecyclerAdapter);

        GridLayoutManager mgr = new GridLayoutManager(this, spanCount);
        mJoinedUsers.setLayoutManager(mgr);

        if(toolBar == null){
            toolBar = (Toolbar) findViewById(R.id.toolbar);
        }
        setSupportActionBar(toolBar);
        toolBar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onBackPressed();
            }
        });

        if(mBtnSpeaking == null){
            mBtnSpeaking = (Button) findViewById(R.id.btn_start_or_stop_speaking);
        }
        mBtnSpeaking.setEnabled(false);
        if(mInTurnSpeaking == null){
            mInTurnSpeaking = (TextView) findViewById(R.id.in_turn_speaking);
        }
        mInTurnSpeaking.setEnabled(false);
        if(mEndInTurnSpeaking == null){
            mEndInTurnSpeaking = (TextView) findViewById(R.id.end_in_turn_speaking);
        }
        mEndInTurnSpeaking.setEnabled(false);
        if(mTextRole == null){
            mTextRole = (TextView) findViewById(R.id.wolf_role);
        }
        mTextRole.setVisibility(View.INVISIBLE);
    }

    @Override
    protected Handler.Callback getHandlerCallback() {
        return mHandlerCallback;
    }

    protected boolean handleUIMessage(Message msg) {
        switch (msg.what) {
            case MsgIds.UPDATE_COUNT_TIMER: {
                mTimerView.setText(msg.arg1 + "s");
                if (msg.arg1 > 0) {
                    if (msg.arg1 == kSpeakingTimerInterval) {
                        mTimerView.setVisibility(View.VISIBLE);
                    }

                    Message newMsg = Message.obtain(msg);
                    newMsg.arg1 = msg.arg1 - 1;
                    mHandler.sendMessageDelayed(newMsg, 1000);
                }
            }
            return true;
        }
        return false;
    }

    /**
     * 根据推流推流方式取得推流 flag
     *
     * @return {@link com.zego.zegoliveroom.constants.ZegoConstants.PublishFlag}
     */
    protected int getPublishFlag() {
        return (currentPublishMode == PublishMode.Low_Cost) ?
                ZegoConstants.PublishFlag.SingleAnchor : ZegoConstants.PublishFlag.JoinPublish;
    }

    protected ZegoUser[] getCurrentMembers() {
        ZegoUser[] members = new ZegoUser[allWolfMembers.size()];
        int index = 0;
        for (WolfInfo wolf : allWolfMembers) {
            members[index++] = wolf;
        }
        return members;
    }

    protected WolfInfo getWolfById(String userId) {
        for (WolfInfo wolf : allWolfMembers) {
            if (userId.equals(wolf.getUserId())) {
                return wolf;
            }
        }
        return null;
    }

    protected WolfInfo getMyInfo() {
        String userId = PreferenceUtil.getInstance().getUserID();
        return getWolfById(userId);
    }

    protected void startTalking() {
        mBtnSpeaking.setText(R.string.end_speaking);
        mTextTips.setText(R.string.mode_updating_system);

        zegoLiveRoom.enableMic(true);
        zegoLiveRoom.enableCamera(true);
        if (currentPublishMode == PublishMode.Super_Low_Delay) {
            sendStartSpeakingCommand(PreferenceUtil.getInstance().getUserID(), new IZegoCustomCommandCallback() {
                @Override
                public void onSendCustomCommand(int errorCode, String roomId) {
                    recordLog("通知别人，自己开始说话返回：%d", errorCode);
                    if (errorCode == 0) {
                        isSpeaking = true;
                        mTextTips.setText(R.string.is_speaking);

                        WolfInfo wolf = getMyInfo();
                        wolf.setState(WolfInfo.SpeakingState.isSpeaking);
                        mRecyclerAdapter.updateItem(wolf);
                        if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
                            mCurrentSpeakingHead.setVisibility(View.VISIBLE);
                            zegoLiveRoom.setPreviewView(mCurrentSpeakingHead);
                            zegoLiveRoom.startPreview();
                        }
                    } else {
                        mBtnSpeaking.setText(R.string.start_speaking);
                        mTextTips.setText(R.string.mode_update_system_failed);

                        zegoLiveRoom.enableMic(false);
                        zegoLiveRoom.enableCamera(false);
                    }
                }
            });
        } else {
            doPublish(roomName);
        }
    }

    protected String doPublish(String roomName) {
        zegoLiveRoom.setWaterMarkImagePath(null);

        Rect zeroRect = new Rect(0, 0, 0, 0);
        zegoLiveRoom.setPreviewWaterMarkRect(zeroRect);
        zegoLiveRoom.setPublishWaterMarkRect(zeroRect);

        // 开启流量自动控制
        int properties = ZegoConstants.ZegoTrafficControlProperty.ZEGOAPI_TRAFFIC_FPS
                | ZegoConstants.ZegoTrafficControlProperty.ZEGOAPI_TRAFFIC_RESOLUTION;
        zegoLiveRoom.enableTrafficControl(properties, true);

        String streamId = ZegoRoomUtil.getPublishStreamID();
        int publishFlag = getPublishFlag();
        boolean success = zegoLiveRoom.startPublishing(streamId, roomName, publishFlag);
        recordLog("推流(流Id: %s)成功？%s", streamId, success);

        return success ? streamId : null;
    }

    protected String publishWithoutPreview(String roomName) {
        dontPreviewWhenPublishSuccess = true;
        zegoLiveRoom.enableMic(false);
        zegoLiveRoom.enableCamera(false);
        return doPublish(roomName);
    }

    protected void handleStartSpeakingCommand(JSONObject json) {
        String userId = json.optString(kSpeakingUserIdKey);
        if (TextUtils.isEmpty(userId)) return;

        WolfInfo wolfInfo = getWolfById(userId);
        if (wolfInfo == null || isMe(userId)) return;

        wolfInfo.setState(WolfInfo.SpeakingState.isSpeaking);
        mRecyclerAdapter.updateItem(wolfInfo);

        if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
            mCurrentSpeakingHead.setVisibility(View.VISIBLE);
            zegoLiveRoom.setViewMode(ZegoVideoViewMode.ScaleAspectFill, wolfInfo.getStreamId());
            zegoLiveRoom.startPlayingStream(wolfInfo.getStreamId(), mCurrentSpeakingHead);
        }
    }

    protected void handleStreamAdded(ZegoStreamInfo[] streamList, String roomId) {
        for (ZegoStreamInfo stream : streamList) {
            recordLog("handleStreamAdded, streamId: %s, from user: %s", stream.streamID, stream.userID);
            WolfInfo wolf = getWolfById(stream.userID);
            if (wolf == null) continue;

            wolf.setState(WolfInfo.SpeakingState.isSpeaking);
            wolf.setStreamId(stream.streamID);
            mRecyclerAdapter.updateItem(wolf);

            if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
                if (isMe(stream.userID)) {
                    zegoLiveRoom.setPreviewViewMode(ZegoVideoViewMode.ScaleAspectFill);
                    zegoLiveRoom.setPreviewView(mCurrentSpeakingHead);
                    zegoLiveRoom.startPreview();
                } else {
                    zegoLiveRoom.setViewMode(ZegoVideoViewMode.ScaleAspectFill, stream.streamID);
                    zegoLiveRoom.startPlayingStream(stream.streamID, mCurrentSpeakingHead);
                }
                bindStream2SpeakingHeaderViewAndShow(stream.streamID);
            }
        }
    }

    protected void handleStreamDeleted(ZegoStreamInfo[] streamList, String roomId) {
        for (ZegoStreamInfo stream : streamList) {
            recordLog("handleStreamDeleted, streamId: %s, from user: %s", stream.streamID, stream.userID);
            WolfInfo wolf = getWolfById(stream.userID);
            if (wolf == null) continue;

            wolf.setState(WolfInfo.SpeakingState.isIdle);
            wolf.setStreamId(null);
            mRecyclerAdapter.updateItem(wolf);

            if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {

                if (isMe(stream.userID)) {
                    zegoLiveRoom.setPreviewView(null);
                    zegoLiveRoom.stopPreview();
                    unBindStreamFromSpeakingHeaderViewAndHide();
                } else {
                    zegoLiveRoom.stopPlayingStream(stream.streamID);
                    String bundleStreamId = (String)mCurrentSpeakingHead.getTag(R.id.bundle_stream_id);
                    if (TextUtils.equals(bundleStreamId, stream.streamID)) {
                        unBindStreamFromSpeakingHeaderViewAndHide();
                    }
                }

            }
        }
    }

    protected void sendStartSpeakingCommand(String userId, IZegoCustomCommandCallback callback) {
        JSONObject json = new JSONObject();
        try {
            json.put(kSpeakingCommandKey, SpeakingCmd.StartSpeaking);
            json.put(kSpeakingUserIdKey, userId);
        } catch (JSONException e) {
        }

        zegoLiveRoom.sendCustomCommand(getCurrentMembers(), json.toString(), callback);
    }

    protected void bindStream2SpeakingHeaderViewAndShow(String streamId) {
        mCurrentSpeakingHead.setTag(R.id.bundle_stream_id, streamId);
        mCurrentSpeakingHead.setVisibility(View.VISIBLE);
    }

    protected void unBindStreamFromSpeakingHeaderViewAndHide() {
        mCurrentSpeakingHead.setVisibility(View.GONE);
        mCurrentSpeakingHead.setTag(R.id.bundle_stream_id, null);
    }

    static protected JSONObject encodeWolfInfo(WolfInfo wolf) throws JSONException {
        JSONObject json = new JSONObject();
        json.put(kUserIdKey, wolf.getUserId());
        json.put(kUserNameKey, wolf.getUserName());
        json.put(kUserIndexKey, wolf.getIndex());
        json.put(kUserStateKey, wolf.getState().intValue());
        return json;
    }

    static protected WolfInfo decodeWolfInfo(JSONObject jsonObject) {
        if (jsonObject == null || jsonObject.length() == 0) return null;

        int userIndex = jsonObject.optInt(kUserIndexKey);
        String userId = jsonObject.optString(kUserIdKey);
        String userName = jsonObject.optString(kUserNameKey);
        int _speakingState = jsonObject.optInt(kUserStateKey);
        WolfInfo.SpeakingState speakingState = WolfInfo.SpeakingState.valueOf(_speakingState);

        WolfInfo wolf = new WolfInfo(userId, userName);
        wolf.setIndex(userIndex);
        wolf.setState(speakingState);
        return wolf;
    }

    static protected boolean isMe(String userId) {
        return (TextUtils.isEmpty(userId) || userId.equals(PreferenceUtil.getInstance().getUserID()));
    }

    protected static class RecyclerGridViewAdapter extends RecyclerView.Adapter<WolfHeadViewHolder> {
        private LayoutInflater layoutInflater;

        private LinkedList<WolfInfo> mData;
        private ZegoLiveRoom _zegoLiveRoom;

        private int currentSpeakingMode = SpeakingMode.FreeSpeakingMode;
        private PublishMode currentPublishMode = PublishMode.Low_Delay;

        RecyclerGridViewAdapter(Context context) {
            layoutInflater = LayoutInflater.from(context);
            mData = new LinkedList<>();
            _zegoLiveRoom = ZegoApiManager.getInstance().getZegoLiveRoom();
        }

        @Override
        public WolfHeadViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            View view = layoutInflater.inflate(R.layout.view_wolf_item, parent, false);
            return new WolfHeadViewHolder(view);
        }

        @Override
        public void onBindViewHolder(WolfHeadViewHolder holder, int position) {
            if (holder == null) return;

            WolfInfo wolf = mData.get(position);
            holder.serialNumber.setText(String.valueOf(wolf.getIndex()));
            holder.name.setText(wolf.getUserName());
            holder.streamId = wolf.getStreamId();
            if (TextUtils.isEmpty(holder.streamId)) {
                holder.headImg.setVisibility(View.INVISIBLE);
                holder.itemView.setBackgroundResource(R.color.bg_gray);
                return;
            }

            WolfInfo.SpeakingState speakState = wolf.getState();
            if (speakState == WolfInfo.SpeakingState.isSpeaking) {
                bindSpeakingViewHolder(holder, wolf);
            } else {
                bindIdleViewHolder(holder, wolf, speakState);
            }
        }

        @Override
        public void onViewRecycled(WolfHeadViewHolder holder) {
//            if (!TextUtils.isEmpty(holder.streamId)) {
//                _zegoLiveRoom.stopPlayingStream(holder.streamId);
//                holder.headImg.setVisibility(View.INVISIBLE);
//            }
        }

        @Override
        public int getItemCount() {
            return mData.size();
        }

        private void bindSpeakingViewHolder(WolfHeadViewHolder holder, WolfInfo wolfInfo) {
            if (currentSpeakingMode == SpeakingMode.FreeSpeakingMode) {
                holder.headImg.setVisibility(View.VISIBLE);
                if (isMe(wolfInfo.getUserId())) {
                    _zegoLiveRoom.setPreviewViewMode(ZegoVideoViewMode.ScaleAspectFill);
                    _zegoLiveRoom.setPreviewView(holder.headImg);
                    _zegoLiveRoom.startPreview();
                } else {
                    _zegoLiveRoom.setViewMode(ZegoVideoViewMode.ScaleAspectFill, holder.streamId);
                    _zegoLiveRoom.startPlayingStream(wolfInfo.getStreamId(), holder.headImg);
                }
            } else {
                // 轮流说话模式会显示大头像，小头像用深色背景标识即可
                holder.headImg.setVisibility(View.INVISIBLE);
                holder.itemView.setBackgroundResource(R.color.bg_gray_deep);
            }
        }

        private void bindIdleViewHolder(WolfHeadViewHolder holder, WolfInfo wolfInfo, WolfInfo.SpeakingState speakState) {
            if (currentSpeakingMode == SpeakingMode.FreeSpeakingMode) {
                if (isMe(wolfInfo.getUserId())) {
                    _zegoLiveRoom.setPreviewView(null);
                    _zegoLiveRoom.stopPreview();
                } else {
                    _zegoLiveRoom.stopPlayingStream(wolfInfo.getStreamId());
                }
            }

            holder.headImg.setVisibility(View.INVISIBLE);
            if (speakState == WolfInfo.SpeakingState.isIdle) {
                holder.itemView.setBackgroundResource(R.color.bg_gray);
            } else if (speakState == WolfInfo.SpeakingState.allowSpeaking) {
                holder.itemView.setBackgroundResource(R.color.bg_gray_deep);
            }
        }

        public void setSpeakingModeAndPublishMode(int speakingMode, PublishMode publishMode) {
            currentSpeakingMode = speakingMode;
            currentPublishMode = publishMode;
        }

        public void updateData(LinkedList<WolfInfo> data) {
            mData.clear();
            mData.addAll(data);

            notifyDataSetChanged();
        }

        public void updateItem(WolfInfo wolf) {
            int pos = -1;
            for (WolfInfo _wolf : mData) {
                pos ++;
                if (_wolf.equals(wolf)) {
                    _wolf.update(wolf);
                    notifyItemChanged(pos);
                    break;
                }
            }
        }

        public void insertItem(WolfInfo wolf) {
            if (wolf != null) {
                mData.add(wolf);
                notifyItemInserted(mData.size() - 1);
            }
        }

        public void deleteItem(WolfInfo wolf) {
            int pos = -1;
            for (WolfInfo _wolf : mData) {
                pos ++;
                if (_wolf.equals(wolf)) {
                    mData.remove(_wolf);
                    notifyItemRemoved(pos);
                    break;
                }
            }
        }
    }

    protected static class WolfHeadViewHolder extends RecyclerView.ViewHolder {
        TextureView headImg;
        TextView serialNumber;
        TextView name;

        String streamId;

        public WolfHeadViewHolder(View itemView) {
            super(itemView);

            headImg = (TextureView)itemView.findViewById(R.id.head_img);
            serialNumber = (TextView)itemView.findViewById(R.id.txt_serial_number);
            name = (TextView)itemView.findViewById(R.id.txt_name);
        }
    }

    /**
     * RecyclerView Item间距
     */
    protected static class GridSpacingItemDecoration extends RecyclerView.ItemDecoration {

        private int spanCount;
        private int spacing;
        private boolean includeEdge;

        /**
         *
         * @param spanCount 每行多少个元素
         * @param spacing 元素间间距
         * @param includeEdge 边缘地带是否需要间距。false 无间距
         */
        public GridSpacingItemDecoration(int spanCount, int spacing, boolean includeEdge) {
            this.spanCount = spanCount;
            this.spacing = spacing;
            this.includeEdge = includeEdge;
        }

        @Override
        public void getItemOffsets(Rect outRect, View view, RecyclerView parent, RecyclerView.State state) {
            int position = parent.getChildAdapterPosition(view); // item position
            int column = position % spanCount; // item column

            if (includeEdge) {
                outRect.left = spacing - column * spacing / spanCount; // spacing - column * ((1f / spanCount) * spacing)
                outRect.right = (column + 1) * spacing / spanCount; // (column + 1) * ((1f / spanCount) * spacing)

                if (position < spanCount) { // top edge
                    outRect.top = spacing;
                }
                outRect.bottom = spacing; // item bottom
            } else {
                outRect.left = column * spacing / spanCount; // column * ((1f / spanCount) * spacing)
                outRect.right = spacing - (column + 1) * spacing / spanCount; // spacing - (column + 1) * ((1f /    spanCount) * spacing)
                if (position >= spanCount) {
                    outRect.top = spacing; // item top
                }
            }
        }
    }
}

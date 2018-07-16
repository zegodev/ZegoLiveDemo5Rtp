package com.zego.livedemo5.videofilter;

import android.graphics.SurfaceTexture;
import android.opengl.GLES11Ext;
import android.opengl.GLES20;
import android.os.Build;
import android.os.Handler;
import android.os.HandlerThread;
import android.view.Surface;


import com.zego.livedemo5.videocapture.ve_gl.EglBase;
import com.zego.livedemo5.videocapture.ve_gl.EglBase14;
import com.zego.livedemo5.videocapture.ve_gl.GlRectDrawer;
import com.zego.livedemo5.videocapture.ve_gl.GlUtil;
import com.zego.zegoavkit2.videofilter.ZegoVideoFilter;

import java.nio.ByteBuffer;
import java.util.concurrent.CountDownLatch;

/**
 * Created by robotding on 17/3/28.
 */

public class VideoFilterSurfaceTextureDemo2 extends ZegoVideoFilter implements SurfaceTexture.OnFrameAvailableListener {
    private ZegoVideoFilter.Client mClient = null;
    private HandlerThread mThread = null;
    private volatile Handler mHandler = null;

    private EglBase mDummyContext = null;
    private EglBase mEglContext = null;
    private int mInputWidth = 0;
    private int mInputHeight = 0;
    private int mOutputWidth = 0;
    private int mOutputHeight = 0;
    private SurfaceTexture mInputSurfaceTexture = null;
    private int mInputTextureId = 0;
    private int mCopyTextureId = 0;
    private Surface mOutputSurface = null;
    private boolean mIsEgl14 = false;

    private GlRectDrawer mDrawer = null;
    private float[] transformationMatrix = new float[]{1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    @Override
    protected void allocateAndStart(ZegoVideoFilter.Client client) {
        mClient = client;
        mThread = new HandlerThread("video-filter");
        mThread.start();
        mHandler = new Handler(mThread.getLooper());

        mInputWidth = 0;
        mInputHeight = 0;

        final CountDownLatch barrier = new CountDownLatch(1);
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                mDummyContext = EglBase.create(null, EglBase.CONFIG_PIXEL_BUFFER);

                try {
                    mDummyContext.createDummyPbufferSurface();
                    mDummyContext.makeCurrent();
                } catch (RuntimeException e) {
                    // Clean up before rethrowing the exception.
                    mDummyContext.releaseSurface();
                    throw e;
                }

                mInputTextureId = GlUtil.generateTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES);
                mInputSurfaceTexture = new SurfaceTexture(mInputTextureId);
                mInputSurfaceTexture.setOnFrameAvailableListener(VideoFilterSurfaceTextureDemo2.this);
                mInputSurfaceTexture.detachFromGLContext();

                mEglContext = EglBase.create(mDummyContext.getEglBaseContext(), EglBase.CONFIG_RECORDABLE);
                mIsEgl14 = EglBase14.isEGL14Supported();

                barrier.countDown();
            }
        });
        try {
            barrier.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void stopAndDeAllocate() {
        final CountDownLatch barrier = new CountDownLatch(1);
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                release();
                barrier.countDown();
            }
        });

        try {
            barrier.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        mHandler = null;

        mThread.quit();
        mThread = null;

        mClient.destroy();
        mClient = null;
    }

    @Override
    protected int supportBufferType() {
        return BUFFER_TYPE_SURFACE_TEXTURE;
    }

    @Override
    protected int dequeueInputBuffer(final int width, final int height, int stride) {
        if (stride != width * 4) {
            return -1;
        }

        if (mInputWidth != width || mInputHeight != height) {
            if (mClient.dequeueInputBuffer(width, height, stride) < 0) {
                return -1;
            }

            mInputWidth = width;
            mInputHeight = height;

            final SurfaceTexture surfaceTexture = mClient.getSurfaceTexture();
            final CountDownLatch barrier = new CountDownLatch(1);
            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    setOutputSurface(surfaceTexture, width, height);
                    barrier.countDown();
                }
            });
            try {
                barrier.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        return 0;
    }

    @Override
    protected ByteBuffer getInputBuffer(int index) {
        return null;
    }

    @Override
    protected void queueInputBuffer(int bufferIndex, int width, int height, int stride, long timestamp_100n) {
    }

    @Override
    protected SurfaceTexture getSurfaceTexture() {
        return mInputSurfaceTexture;
    }

    @Override
    protected void onProcessCallback(int textureId, int width, int height, long timestamp_100n) {

    }

    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {
        mEglContext.makeCurrent();
        if (mDrawer == null) {
            mDrawer = new GlRectDrawer();
        }

        if (mCopyTextureId == 0) {
            mCopyTextureId = GlUtil.generateTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES);
            surfaceTexture.attachToGLContext(mCopyTextureId);
        }
        surfaceTexture.updateTexImage();
        long timestampNs = surfaceTexture.getTimestamp();

        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        mDrawer.drawOes(mCopyTextureId, transformationMatrix,
                        mOutputWidth, mOutputHeight, 0, 0, mOutputWidth, mOutputHeight);

        if (mIsEgl14) {
            ((EglBase14) mEglContext).swapBuffers(timestampNs);
        } else {
            mEglContext.swapBuffers();
        }

        mEglContext.detachCurrent();
    }

    private void setOutputSurface(SurfaceTexture surfaceTexture, int width, int height) {
        if (mEglContext.hasSurface()) {
            mEglContext.makeCurrent();
            if (mDrawer != null) {
                mDrawer.release();
                mDrawer = null;
            }

            if (mCopyTextureId != 0) {
                int[] textures = new int[] {mCopyTextureId};
                GLES20.glDeleteTextures(1, textures, 0);
                mCopyTextureId = 0;
            }

            mEglContext.releaseSurface();
        }

        if (mOutputSurface != null) {
            mOutputSurface.release();
            mOutputSurface = null;
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1) {
            surfaceTexture.setDefaultBufferSize(width, height);
        }
        mOutputSurface = new Surface(surfaceTexture);
        mOutputWidth = width;
        mOutputHeight = height;

        mEglContext.createSurface(mOutputSurface);
    }

    private void release() {
        mInputSurfaceTexture.release();
        mInputSurfaceTexture = null;

        mDummyContext.makeCurrent();
        if (mInputTextureId != 0) {
            int[] textures = new int[] {mInputTextureId};
            GLES20.glDeleteTextures(1, textures, 0);
            mInputTextureId = 0;
        }
        mDummyContext.release();
        mDummyContext = null;

        if (mEglContext.hasSurface()) {
            mEglContext.makeCurrent();
            if (mDrawer != null) {
                mDrawer.release();
                mDrawer = null;
            }

            if (mCopyTextureId != 0) {
                int[] textures = new int[] {mCopyTextureId};
                GLES20.glDeleteTextures(1, textures, 0);
                mCopyTextureId = 0;
            }
        }
        mEglContext.release();
        mEglContext = null;

        if (mOutputSurface != null) {
            mOutputSurface.release();
            mOutputSurface = null;
        }
    }
}

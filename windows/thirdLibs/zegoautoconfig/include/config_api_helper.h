//

#ifndef ZEGOCONFIGAPI_CONFIG_API_HELPER_HPP
#define ZEGOCONFIGAPI_CONFIG_API_HELPER_HPP


#ifdef ZEGOCONFIG_EXPORTS
	#define ZEGOCONFIG_API __declspec(dllexport)
#elif defined(ZEGOCONFIG_STATIC)
	#define ZEGOCONFIG_API // * nothing
#else
	#define ZEGOCONFIG_API __declspec(dllimport)
#endif

#include <config_api.hpp>
#include <memory>
#include <mutex>

namespace zego {
	class ZEGOCONFIG_API ConfigApiHelper {
	public:

		static std::shared_ptr<ConfigApiHelper> sharedInstance();

		std::shared_ptr<ConfigApi> api;

	private:
		ConfigApiHelper();
	};
}

#endif

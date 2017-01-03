#pragma once
#include <memory>
#include <functional>
#include <vector>

namespace SL {
	namespace Screen_Capture {
		
		struct Monitor{
			int Index;
			int Height;
			int Width;
			//Offsets are the number of pixels that a monitor can be from the origin. For example, users can shuffle their monitors around so this affects their offset.
			int OffsetX;
			int OffsetY;
			std::string Name;
		};
		
		struct ImageRect {
			int    left = 0;
			int    top = 0;
			int    right = 0;
			int    bottom = 0;
		};
		std::vector<Monitor> GetMonitors();
		typedef std::function<void(const char* data, const int pixelstride /*in bytes*/, const Monitor& monitor)> CaptureEntireMonitorCallback;
		typedef std::function<void(const char* data, const int pixelstride /*in bytes*/, const Monitor& monitor, const ImageRect& rect)> CaptureDifMonitorCallback;

		class ScreenCaptureManagerImpl;
		class ScreenCaptureManager {
			std::unique_ptr<ScreenCaptureManagerImpl> _ScreenCaptureManagerImpl;

		public:
			ScreenCaptureManager();
			~ScreenCaptureManager();
			//set this callback if you want to capture the entire Montitor
			void Set_CapturCallback(CaptureEntireMonitorCallback img_cb);
			//set this callback if you want to capture just differences between the frames
			void Set_CapturCallback(CaptureDifMonitorCallback img_cb);

			void StartCapturing(int min_interval);
			void StopCapturing();
		};		
		enum DUPL_RETURN
		{
			DUPL_RETURN_SUCCESS = 0,
			DUPL_RETURN_ERROR_EXPECTED = 1,
			DUPL_RETURN_ERROR_UNEXPECTED = 2
		};
		const int PixelStride = 4;
	
    }
}
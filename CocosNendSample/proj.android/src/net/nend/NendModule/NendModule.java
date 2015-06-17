package net.nend.NendModule;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.content.Context;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import net.nend.android.NendAdListener;
import net.nend.android.NendAdView;

public class NendModule {
	
	enum LayoutType {
		TOP, 
		BOTTOM,
		USER
	}

	private static NendAdView nendAdView;
	private static WindowManager mWm;
	private static LayoutType mType;
	private static float mPosX;
	private static float mPosY;

	// 広告の初期化
	public static void createAdView(final String apiKey, final String spotID, final float x, final float y, final boolean isAdjust) {
		mType = LayoutType.USER;
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView == null) {
					int intSpotID = Integer.parseInt(spotID);
					mPosX = x;
					mPosY = y;
					
					nendAdView = new NendAdView(activity, intSpotID, apiKey, isAdjust);
					nendAdView.setListener(sAdListener);
					nendAdView.loadAd();
				}
			}
		});
	}

	// 広告の初期化
	public static void createAdViewBottom(final String apiKey, final String spotID, final boolean isAdjust) {
		mType = LayoutType.BOTTOM;
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView == null) {
					int intSpotID = Integer.parseInt(spotID);

					nendAdView = new NendAdView(activity, intSpotID, apiKey, isAdjust);
					nendAdView.setListener(sAdListener);
				
					nendAdView.loadAd();
				}
			}
		});
	}

	// 広告の初期化
	public static void createAdViewTop(final String apiKey, final String spotID, final boolean isAdjust) {
		mType = LayoutType.TOP;
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView == null) {
					int intSpotID = Integer.parseInt(spotID);

					nendAdView = new NendAdView(activity, intSpotID, apiKey, isAdjust);
					nendAdView.setListener(sAdListener);

					nendAdView.loadAd();
				}
			}
		});
	}

	// 広告の非表示
	public static void hideAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.setVisibility(View.GONE);
				}
			}
		});
	}

	// 広告の再表示
	public static void showAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.setVisibility(View.VISIBLE);
				}
			}
		});
	}
	
	// 広告の一時停止
	public static void pauseAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.pause();
				}
			}
		});
	}

	// 広告の再開
	public static void resumeAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {

				if (nendAdView != null) {
					nendAdView.resume();
				}
			}
		});
	}
	
	// 解放
	public static void releaseAdView() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(nendAdView != null){
					nendAdView.removeAllViews();
					nendAdView.removeListener();
				}
				if(mWm != null){
					mWm.removeView(nendAdView);
					nendAdView = null;
					mWm = null;
				}else{
					nendAdView = null;
				}
			}
		});
	}
	
	private static WindowManager.LayoutParams layoutParamsWindowManager() {
		WindowManager.LayoutParams layoutParams = new WindowManager.LayoutParams();
		layoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
		layoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
		layoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
		layoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
		return layoutParams;
	}
	
	private static void layoutViewTop() {
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView != null) {
					mWm = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
					WindowManager.LayoutParams layoutParams = layoutParamsWindowManager();
					layoutParams.gravity = Gravity.TOP;
					mWm.addView(nendAdView, layoutParams);
				}
			}
		});
	}
	
	private static void layoutViewBottom() {
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView != null) {
					mWm = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
					WindowManager.LayoutParams layoutParams = layoutParamsWindowManager();
					layoutParams.gravity = Gravity.BOTTOM;
					mWm.addView(nendAdView, layoutParams);				
				}
			}
		});
	}
	
	private static void layoutViewUser() {
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (nendAdView != null) {
					mWm = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
					WindowManager.LayoutParams layoutParams = layoutParamsWindowManager();
					layoutParams.gravity = Gravity.TOP | Gravity.LEFT;
					layoutParams.x = (int)mPosX;
					layoutParams.y = (int)mPosY;
					mWm.addView(nendAdView, layoutParams);
				}
			}
		});
	}
	
	private static NendAdListener sAdListener = new NendAdListener() {
		
		@Override
		public void onReceiveAd(NendAdView arg0) {
			NendModule.onReceiveAd();
			
			if (mWm != null) {
				return;
			}
			
			switch (mType) {
			case TOP:
				layoutViewTop();
				break;
			case BOTTOM:
				layoutViewBottom();
				break;
			case USER:
				layoutViewUser();
				break;

			default:
				break;
			}	
		}
		
		@Override
		public void onFailedToReceiveAd(NendAdView arg0) {
			NendModule.onFailedToReceiveAd();
		}
		
		@Override
		public void onDismissScreen(NendAdView arg0) {
			NendModule.onDismissScreen();
		}
		
		@Override
		public void onClick(NendAdView arg0) {
			NendModule.onClick();
		}
	};
	
	public static native void onReceiveAd();
	public static native void onFailedToReceiveAd();
	public static native void onDismissScreen();
	public static native void onClick();
}

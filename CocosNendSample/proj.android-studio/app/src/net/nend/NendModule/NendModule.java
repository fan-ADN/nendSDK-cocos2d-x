package net.nend.NendModule;

import android.app.Activity;
import android.content.Context;
import android.graphics.Point;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;

import net.nend.NendModule.NendAdViewData.LayoutType;
import net.nend.NendModule.NendAdViewData.NendAdState;
import net.nend.android.NendAdListener;
import net.nend.android.NendAdView;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.util.HashMap;

class NendAdViewData {
	
	enum LayoutType {
		TOP, 
		BOTTOM,
		USER
	}
	
	enum NendAdState {
		HIDE, 
		SHOW,
		PAUSE,
		RESUME,
		RELEASE
	}

	NendAdView nendAdView;
	Point pos;
	LayoutType layout;
	boolean isExist;

}


public class NendModule {
	
	enum EventListenerType {
		onReceiveAd,
		onFailedToReceiveAd,
		onClick
	}

	private static HashMap<String, NendAdViewData> mNendAdHashMap = new HashMap<>();
	
	
	private static WindowManager.LayoutParams layoutParamsWindowManager() {
		WindowManager.LayoutParams layoutParams = new WindowManager.LayoutParams();
		layoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
		layoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
		layoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
		layoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
		return layoutParams;
	}
	
	private static void layoutViews(final String spotID, final LayoutType type) {
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				NendAdViewData holdNendAd = mNendAdHashMap.get(spotID);
				if (holdNendAd != null) {
					WindowManager window = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
					WindowManager.LayoutParams layoutParams = layoutParamsWindowManager();
					
					switch (type) {
					case TOP:
						layoutParams.gravity = Gravity.TOP;
						break;
					case BOTTOM:
						layoutParams.gravity = Gravity.BOTTOM;
						break;
					case USER:
						layoutParams.gravity = Gravity.TOP | Gravity.LEFT;
						layoutParams.x = holdNendAd.pos.x;
						layoutParams.y = holdNendAd.pos.y;
						break;

					default:
						break;
					}
					
					holdNendAd.isExist = true;
					window.addView(holdNendAd.nendAdView, layoutParams);
				}
			}
		});
	}
	
	private static void releaseViews(NendAdViewData holdNendAd, Activity activity) {
		holdNendAd.nendAdView.removeAllViews();
		holdNendAd.nendAdView.removeListener();
		WindowManager window = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
		window.removeView(holdNendAd.nendAdView);
		holdNendAd.nendAdView = null;
		holdNendAd = null;
	}
	
	private static void createNADView(final String apiKey, final String spotID, final boolean isAdjust, final LayoutType type, final Point pos) {
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (!mNendAdHashMap.containsKey(spotID)) {
					int intSpotID = Integer.parseInt(spotID);
					NendAdView nendAdView = new NendAdView(activity, intSpotID, apiKey, isAdjust);
					nendAdView.setListener(sAdListener);
					nendAdView.setTag(spotID);
					nendAdView.loadAd();

					NendAdViewData nendAdViewData = new NendAdViewData();
					nendAdViewData.nendAdView = nendAdView;
					nendAdViewData.pos = pos;
					nendAdViewData.layout = type;
					nendAdViewData.isExist = false;
					mNendAdHashMap.put(spotID, nendAdViewData);
				}
			}
 		});
	}
	
	private static void selectAdState(NendAdViewData nendAd, final NendAdState state, Activity activity) {
		if (nendAd != null) {
			switch (state) {
			case SHOW:
				nendAd.nendAdView.setVisibility(View.VISIBLE);
				break;
			case HIDE:
				nendAd.nendAdView.setVisibility(View.GONE);
				break;
			case PAUSE:
				nendAd.nendAdView.pause();
				break;
			case RESUME:
				nendAd.nendAdView.resume();
				break;
			case RELEASE:
				releaseViews(nendAd, activity);			
				break;
			default:
				break;
			}	
		}
	}
	
	private static void controlAdState(final String spotID, final NendAdState state) {
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (spotID != null) {
					NendAdViewData holdNendAd = mNendAdHashMap.get(spotID);
					selectAdState(holdNendAd, state, activity);
					if (state == NendAdState.RELEASE) {
						mNendAdHashMap.remove(spotID);
					}
				}else {
					for (NendAdViewData holdNendAd : mNendAdHashMap.values()) {
						selectAdState(holdNendAd, state, activity);
					}
					if (state == NendAdState.RELEASE) {
						mNendAdHashMap.clear();
					}
				}
			}
		});	
	}

	// 広告の初期化(位置指定)
	public static void createAdView(final String apiKey, final String spotID, final float x, final float y, final boolean isAdjust) {
		createNADView(apiKey, spotID, isAdjust, LayoutType.USER, new Point((int)x, (int)y));
	}

	// 広告の初期化(画面下部中央)
	public static void createAdViewBottom(final String apiKey, final String spotID, final boolean isAdjust) {
		createNADView(apiKey, spotID, isAdjust, LayoutType.BOTTOM, new Point(0, 0));
	}

	// 広告の初期化(画面上部中央)
	public static void createAdViewTop(final String apiKey, final String spotID, final boolean isAdjust) {
		createNADView(apiKey, spotID, isAdjust, LayoutType.TOP, new Point(0, 0));
	}
	
	// 広告の非表示
	public static void hideAdView() {
		hideAdView(null);
	}
	
	// 広告の非表示(spotID指定)
	public static void hideAdView(final String spotID) {
		controlAdState(spotID, NendAdState.HIDE);
	}
	
	// 広告の再表示
	public static void showAdView() {
		showAdView(null);
	}
	
	// 広告の再表示(spotID指定)
	public static void showAdView(final String spotID) {
		controlAdState(spotID, NendAdState.SHOW);
	}
	
	// 広告の一時停止
	public static void pauseAdView() {
		pauseAdView(null);
	}
	
	// 広告の一時停止(spotID)
	public static void pauseAdView(final String spotID) {
		controlAdState(spotID, NendAdState.PAUSE);
	}

	// 広告の再開
	public static void resumeAdView() {
		resumeAdView(null);
	}
	
	// 広告の再開(spotID指定)
	public static void resumeAdView(final String spotID) {
		controlAdState(spotID, NendAdState.RESUME);
	}
	
	// 解放
	public static void releaseAdView() {
		releaseAdView(null);
	}
	
	// 解放(spotID指定)
	public static void releaseAdView(final String spotID) {
		controlAdState(spotID, NendAdState.RELEASE);
	}
	
	private static void EventListener(EventListenerType type, NendAdView adView) {
		
		String keySpotID = (String) adView.getTag();
		NendAdViewData holdNendAd = mNendAdHashMap.get(keySpotID);
		if (holdNendAd != null) {
			int intSpotID = Integer.parseInt(keySpotID);

			switch (type) {
			case onReceiveAd:
				NendModule.onReceiveAd();
				NendModule.onReceiveAdWithSpotId(intSpotID);
				
				if (holdNendAd.isExist) {
					return;
				}
				
				layoutViews(keySpotID, holdNendAd.layout);
				
				break;
			case onFailedToReceiveAd:
				NendModule.onFailedToReceiveAd();
				NendModule.onFailedToReceiveAdWithSpotId(intSpotID);
				break;
			case onClick:
				NendModule.onClick();
				NendModule.onClickWithSpotId(intSpotID);
				break;
			default:
				break;
			}			
		}	
	}
	
	private static NendAdListener sAdListener = new NendAdListener() {
		
		@Override
		public void onReceiveAd(NendAdView adView) {
			EventListener(EventListenerType.onReceiveAd, adView);
		}
		
		@Override
		public void onFailedToReceiveAd(NendAdView adView) {
			EventListener(EventListenerType.onFailedToReceiveAd, adView);
		}
		
		@Override
		public void onClick(NendAdView adView) {
			EventListener(EventListenerType.onClick, adView);
		}
		
		@Override
		public void onDismissScreen(NendAdView adView) {
			// 未サポート
		}
	};
	
	public static native void onReceiveAd();
	public static native void onReceiveAdWithSpotId(final int spotId);
	public static native void onFailedToReceiveAd();
	public static native void onFailedToReceiveAdWithSpotId(final int spotId);
	public static native void onClick();
	public static native void onClickWithSpotId(final int spotId);
}

package net.nend.NendModule;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;

import net.nend.android.NendAdIconLoader;
import net.nend.android.NendAdIconLoader.OnClickListener;
import net.nend.android.NendAdIconLoader.OnFailedListener;
import net.nend.android.NendAdIconLoader.OnReceiveListener;
import net.nend.android.NendAdIconView;
import net.nend.android.NendIconError;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.util.ArrayList;
import java.util.HashMap;

class NendAdIconData {

	NendAdIconLoader iconLoader;
	LinearLayout linearLayout;
	ArrayList<NendAdIconView> arrayList;
	String spotIDString;
	boolean isExist;
}

public class NendIconModule {
	
	enum EventListenerType {
		onReceiveAd, 
		onClick
	}
	
	enum LayoutType {
		TOP, 
		BOTTOM,
		USER
	}
	
	enum IconAdState {
		LOAD,
		HIDE, 
		SHOW,
		PAUSE,
		RESUME,
		RELEASE
	}

	// 広告枠ごとのアイコンを保持するMap
	private static HashMap<String, NendAdIconData> mNendAdIconHashMap = new HashMap<>();

	
	private static WindowManager.LayoutParams layoutParamsWindowManager() {
		WindowManager.LayoutParams layoutParams = new WindowManager.LayoutParams();
		layoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
		layoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
		layoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
		layoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
		return layoutParams;
	}
	
	private static NendAdIconView createNADIcon(Activity activity, boolean isVisible, boolean isSpace, int r, int g, int b) {
		NendAdIconView iconView = new NendAdIconView(activity.getApplicationContext());
		iconView.setTitleVisible(isVisible);
		iconView.setIconSpaceEnabled(isSpace);
		iconView.setTitleColor(Color.rgb(r, g, b));
		return iconView;
	}
	
	private static void layoutPosition(final LayoutType type, final Activity activity, NendAdIconData holdNendAd, final int iconCount, final float x, final float y, final boolean isVisible, final boolean isSpace, final int r, final int g, final int b) {
		switch (type) {
		case TOP:
			createIconViewTopPosition(iconCount, activity, holdNendAd, isVisible, isSpace, r, g, b);
			break;
		case BOTTOM:
			createIconViewBottomPosition(iconCount, activity, holdNendAd, isVisible, isSpace, r, g, b);
			break;
		case USER:
			createIconViewUserPosition(activity, holdNendAd, x, y, isVisible, isSpace, r, g, b);
			break;
		default:
			break;
		}
	}
	
	private static void layoutViews(final LayoutType type, final String spotID, final int iconCount, final float x, final float y, final boolean isVisible, final boolean isSpace, final int r, final int g, final int b) {
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (spotID != null) {
					NendAdIconData holdNendAd = mNendAdIconHashMap.get(spotID);
					if (holdNendAd != null) {
						layoutPosition(type, activity, holdNendAd, iconCount, x, y, isVisible, isSpace, r, g, b);
					}
				}else {
					for (NendAdIconData holdNendAd : mNendAdIconHashMap.values()) {
						if (holdNendAd != null) {
							layoutPosition(type, activity, holdNendAd, iconCount, x, y, isVisible, isSpace, r, g, b);
						}
					}
				}
			}
		});
	}
	
	private static void hideIcon(NendAdIconData holdNendAd) {
		if (holdNendAd != null) {						
			for (NendAdIconView iconView : holdNendAd.arrayList) {
				iconView.setVisibility(View.GONE);
			}
			if (holdNendAd.linearLayout != null) {
				holdNendAd.linearLayout.setVisibility(View.GONE);
			}
		}
	}
	
	private static void showIcon(NendAdIconData holdNendAd) {
		if (holdNendAd != null) {						
			for (NendAdIconView iconView : holdNendAd.arrayList) {
				iconView.setVisibility(View.VISIBLE);
			}
			if (holdNendAd.linearLayout != null) {
				holdNendAd.linearLayout.setVisibility(View.VISIBLE);
			}
		}
	}
	
	private static void releaseIcon(Activity activity, NendAdIconData holdNendAd) {
		holdNendAd.iconLoader = null;
		WindowManager window = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
		if (holdNendAd.linearLayout != null) {
			holdNendAd.linearLayout.removeAllViews();
			window.removeView(holdNendAd.linearLayout);
		}else {
			for (NendAdIconView iconView : holdNendAd.arrayList) {
				window.removeView(iconView);
			}
		}
		holdNendAd.arrayList.clear();
		holdNendAd.arrayList = null;
		holdNendAd = null;
	}
	
	private static void selectIconState(NendAdIconData nendAd, final IconAdState state, Activity activity) {
		if (nendAd != null) {
			switch (state) {
			case LOAD:
				nendAd.iconLoader.loadAd();
				break;
			case SHOW:
				showIcon(nendAd);
				break;
			case HIDE:
				hideIcon(nendAd);
				break;
			case PAUSE:
				nendAd.iconLoader.pause();
				break;
			case RESUME:
				nendAd.iconLoader.resume();
				break;
			case RELEASE:
				releaseIcon(activity, nendAd);			
				break;
			default:
				break;
			}	
		}
	}
	
	private static void controlIconState(final String spotID, final IconAdState state) {
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (spotID != null) {
					NendAdIconData holdNendAd = mNendAdIconHashMap.get(spotID);
					selectIconState(holdNendAd, state, activity);
					if (state == IconAdState.RELEASE) {
						mNendAdIconHashMap.remove(spotID);
					}
				}else {
					for (NendAdIconData holdNendAd : mNendAdIconHashMap.values()) {
						selectIconState(holdNendAd, state, activity);
					}
					if (state == IconAdState.RELEASE) {
						mNendAdIconHashMap.clear();
					}
				}
			}
		});	
	}
	
	private static void eventListener(EventListenerType type, NendAdIconView iconView) {
		for (NendAdIconData holdNendAd : mNendAdIconHashMap.values()) {
			if (holdNendAd != null) {
				for (NendAdIconView holdIconView : holdNendAd.arrayList) {
					if (holdIconView == iconView) {
						int intSpotID = Integer.parseInt(holdNendAd.spotIDString);	
						switch (type) {
						case onReceiveAd:
							NendIconModule.onReceiveIconAd();
 							NendIconModule.onReceiveIconAdWithSpotId(intSpotID);
							break;
						case onClick:
							NendIconModule.onClickIconAd();
							NendIconModule.onClickIconAdWithSpotId(intSpotID);
							break;
						default:
							break;
						}
						return;
					}
				}
			}
		}		
	}
	
	private static void createIconViewTopPosition(final int iconCount, Activity activity, NendAdIconData holdNendAd, boolean isVisible, boolean isSpace, final int r, final int g, final int b) {
		createNendAdIconView(Gravity.TOP, iconCount, activity, holdNendAd, isVisible, isSpace, r, g, b);
	}
	
	private static void createIconViewBottomPosition(final int iconCount, Activity activity, NendAdIconData holdNendAd, boolean isVisible, boolean isSpace, final int r, final int g, final int b) {
		createNendAdIconView(Gravity.BOTTOM, iconCount, activity, holdNendAd, isVisible, isSpace, r, g, b);
	}
	
	private static void createIconViewUserPosition(Activity activity, NendAdIconData holdNendAd, final float x, final float y, boolean isVisible, boolean isSpace, final int r, final int g, final int b) {
		
		//IconViewの生成
		NendAdIconView iconView = createNADIcon(activity, isVisible, isSpace, r, g, b);
		
		WindowManager window = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
		WindowManager.LayoutParams layoutParams = layoutParamsWindowManager();
		layoutParams.gravity = Gravity.TOP | Gravity.LEFT;
		layoutParams.format = PixelFormat.TRANSLUCENT;
		layoutParams.x = (int)x;
		layoutParams.y = (int)y;
		window.addView(iconView, layoutParams);
		
		holdNendAd.linearLayout = null;

		// loaderへiconを追加
		holdNendAd.iconLoader.addIconView(iconView);							
		
		// 制御用にiconを保持
		holdNendAd.arrayList.add(iconView);
		
		holdNendAd.isExist = true;
	}
	
	private static void createNendAdIconView(final int gravity, final int iconCount, Activity activity, NendAdIconData holdNendAd, boolean isVisible, boolean isSpace, final int r, final int g, final int b) {
		
		if (holdNendAd.isExist) {
			return;
		}
		
		// IconViewを設置するレイアウト
		LinearLayout baseLayout = new LinearLayout(activity);
		baseLayout.setGravity(gravity | Gravity.CENTER);
		holdNendAd.linearLayout = baseLayout;
		
		for(int i = 0 ; i < iconCount ; i++){
			
			NendAdIconView iconView = createNADIcon(activity, isVisible, isSpace, r, g, b);
			
			// LinearLayoutへiconを追加
			holdNendAd.linearLayout.addView(iconView);
			
			holdNendAd.iconLoader.addIconView(iconView);
			
			holdNendAd.arrayList.add(iconView);
		}
		
		WindowManager window = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
		WindowManager.LayoutParams layoutParams = layoutParamsWindowManager();
		layoutParams.gravity = gravity;
		layoutParams.format = PixelFormat.TRANSLUCENT;
		window.addView(holdNendAd.linearLayout, layoutParams);
		
		holdNendAd.isExist = true;
	}	
	
	// NendAdIconLoader生成
	public static void createIconLoader(final String apiKey, final String spotID) {
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if (!mNendAdIconHashMap.containsKey(spotID)) {
					int intSpotID = Integer.parseInt(spotID);

					NendAdIconLoader iconLoader = new NendAdIconLoader(activity.getApplicationContext(), intSpotID, apiKey);
					iconLoader.setOnReceiveListener(sOnReceiveListener);
					iconLoader.setOnFailedListener(sOnFailedListener);
					iconLoader.setOnClickListener(sOnClickListener);

					ArrayList<NendAdIconView> adIconViewArray = new ArrayList<>();

					NendAdIconData nendAdIconData = new NendAdIconData();
					nendAdIconData.iconLoader = iconLoader;
					nendAdIconData.arrayList = adIconViewArray;

					nendAdIconData.isExist = false;
					nendAdIconData.spotIDString = spotID;

					mNendAdIconHashMap.put(spotID, nendAdIconData);
				}
			}
		});
	}
	
	// 位置指定でアイコン生成
	public static void createIconView(final float x, final float y){
		createIconView(x, y, null, true, true, 0, 0, 0);
	}
	
	// 位置指定でアイコン生成(spotID指定、タイトル表示指定、余白指定、タイトル文字色指定)
	public static void createIconView(final float x, final float y, final String spotID, final boolean isVisible, final boolean isSpace, final int r, final int g, final int b){		
		layoutViews(LayoutType.USER, spotID, 0, x, y, isVisible, isSpace, r, g, b);
	}
	
	// 画面上部中央にアイコン表示(アイコン数指定)
	public static void createIconViewTop(final int iconCount){
		createIconViewTop(iconCount, null, true, true, 0, 0, 0);
	}
	
	// 画面上部中央にアイコン表示(アイコン数指定、spotID指定、タイトル表示指定、余白指定、タイトル文字色指定)
	public static void createIconViewTop(final int iconCount, final String spotID, final boolean isVisible, final boolean isSpace, final int r, final int g, final int b){
		layoutViews(LayoutType.TOP, spotID, iconCount, 0, 0, isVisible, isSpace, r, g, b);
	}
	
	// 画面下部中央にアイコン表示(アイコン数指定)
	public static void createIconViewBottom(final int iconCount){
		createIconViewBottom(iconCount, null, true, true, 0, 0, 0);
	}
	
	// 画面下部中央にアイコン表示(アイコン数指定、spotID指定、タイトル表示指定、余白指定、タイトル文字色指定)
	public static void createIconViewBottom(final int iconCount, final String spotID, final boolean isVisible, final boolean isSpace, final int r, final int g, final int b){
		layoutViews(LayoutType.BOTTOM, spotID, iconCount, 0, 0, isVisible, isSpace, r, g, b);
	}

	// 定期ロード開始
	public static void loadIconLoader() {
		loadIconLoader(null);
	}
	
	// 定期ロード開始(spotID指定)
	public static void loadIconLoader(final String spotID) {
		controlIconState(spotID, IconAdState.LOAD);
	}
	
	// アイコン非表示
	public static void hideIconView(){
		hideIconView(null);
	}
	
	// アイコン非表示(spotID指定)
	public static void hideIconView(final String spotID){
		controlIconState(spotID, IconAdState.HIDE);
	}
	
	// アイコン再表示
	public static void showIconView(){
		showIconView(null);
	}

	// アイコン再表示(spotID指定)
	public static void showIconView(final String spotID){
		controlIconState(spotID, IconAdState.SHOW);
	}

	// 定期ロード中断
	public static void pauseIconView(){
		pauseIconView(null);
	}
	
	// 定期ロード中断(spotID指定)
	public static void pauseIconView(final String spotID){
		controlIconState(spotID, IconAdState.PAUSE);
	}

	// 定期ロード再開
	public static void resumeIconView(){
		resumeIconView(null);
	}
	
	// 定期ロード再開(spotID指定)
	public static void resumeIconView(final String spotID){
		controlIconState(spotID, IconAdState.RESUME);
	}
	
	// 解放
	public static void releaseIconView(){
		releaseIconView(null);
	}
	
	// 解放(spotID指定)
	public static void releaseIconView(final String spotID){
		hideIconView(spotID);
		controlIconState(spotID, IconAdState.RELEASE);
	}

	private static OnReceiveListener sOnReceiveListener = new OnReceiveListener() {
		@Override
		public void onReceiveAd(NendAdIconView iconView) {
			eventListener(EventListenerType.onReceiveAd, iconView);
		}
	};

	private static OnClickListener sOnClickListener = new OnClickListener() {
		@Override
		public void onClick(NendAdIconView iconView) {
			eventListener(EventListenerType.onClick, iconView);
		}
	};

	private static OnFailedListener sOnFailedListener = new OnFailedListener() {
		@Override
		public void onFailedToReceiveAd(NendIconError iconError) {
			NendAdIconLoader iconLoader = iconError.getLoader();			
			if (iconLoader != null) {
				for (NendAdIconData holdNendAd : mNendAdIconHashMap.values()) {
					if (holdNendAd != null && holdNendAd.iconLoader == iconLoader) {
						NendIconModule.onFailedIconAd();
						int intSpotID = Integer.parseInt(holdNendAd.spotIDString);
						NendIconModule.onFailedIconAdWithSpotId(intSpotID);
					}
				}
			}
		}
	};

	public static native void onReceiveIconAd();
	public static native void onReceiveIconAdWithSpotId(final int spotId);
	public static native void onFailedIconAd();
	public static native void onFailedIconAdWithSpotId(final int spotId);
	public static native void onClickIconAd();
	public static native void onClickIconAdWithSpotId(final int spotId);
}

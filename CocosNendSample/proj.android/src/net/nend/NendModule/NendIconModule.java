package net.nend.NendModule;

import java.util.ArrayList;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.content.Context;
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

public class NendIconModule {

	//表示するアイコン個数
	public static final int ICON_DISPLAY_COUNT = 4;
	//IconLoader
	private static NendAdIconLoader mIconLoader;
	//IconView
	private static ArrayList<NendAdIconView> adIconViewArray;

	private static WindowManager mWm;
	
	private static LinearLayout mBaseLayout;

	public static void createIconLoader(final String apiKey, final String spotID) {
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader == null){
					int intSpotID = Integer.parseInt(spotID);
					mIconLoader = new NendAdIconLoader(activity.getApplicationContext(), intSpotID, apiKey);
					mIconLoader.setOnReceiveListener(sOnReceiveListener);
					mIconLoader.setOnFailedListener(sOnFailedListener);
					mIconLoader.setOnClickListener(sOnClickListener);
					adIconViewArray = new ArrayList<NendAdIconView>();
				}
			}
		});
	}
	
	public static void createIconView(final float x, final float y){

		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					
					//IconViewの生成
					NendAdIconView iconView = new NendAdIconView(activity.getApplicationContext());
			
					if (null == mWm) {
						mWm = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
					}

					WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams();
					mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
					mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
					mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
					mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
					mLayoutParams.gravity = Gravity.TOP | Gravity.LEFT;
					mLayoutParams.format = PixelFormat.TRANSLUCENT;
					mLayoutParams.x = (int)x;
					mLayoutParams.y = (int)y;
					mWm.addView(iconView, mLayoutParams);

					//IconLoaderへ設定
					mIconLoader.addIconView(iconView);
					//IconViewを保持する
					adIconViewArray.add(iconView);
				}
			}
		});
	}

	public static void createIconViewBottom(final int iconCount){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {

				if(mIconLoader != null){

					if (null == mWm) {
						mWm = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
					}

					if (mBaseLayout == null){
						//IconViewを設置するレイアウト
						mBaseLayout = new LinearLayout(activity);
						mBaseLayout.setGravity(Gravity.BOTTOM | Gravity.CENTER);
						
						for(int i = adIconViewArray.size() ; i < iconCount ; i++){
							//iconの生成
							NendAdIconView iconView = new NendAdIconView(activity.getApplicationContext());
							mBaseLayout.addView(iconView);

							//loaderへiconを追加
							mIconLoader.addIconView(iconView);
							//制御用にiconを保持
							adIconViewArray.add(iconView);
						}
						WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams();
						mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
						mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
						mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
						mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
						mLayoutParams.gravity = Gravity.BOTTOM;
						mLayoutParams.format = PixelFormat.TRANSLUCENT;
						mWm.addView(mBaseLayout, mLayoutParams);
					}

				}
			}
		});
	}

	public static void createIconViewTop(final int iconCount){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){

					if (null == mWm) {
						mWm = (WindowManager) activity.getSystemService(Context.WINDOW_SERVICE);
					}

					if (mBaseLayout == null){
						//IconViewを設置するレイアウト
						mBaseLayout = new LinearLayout(activity);
						mBaseLayout.setGravity(Gravity.TOP | Gravity.CENTER);
						
						for(int i = adIconViewArray.size() ; i < iconCount ; i++){
							//iconの生成
							NendAdIconView iconView = new NendAdIconView(activity.getApplicationContext());

							//iconのレイアウト
							mBaseLayout.addView(iconView);

							//loaderへiconを追加
							mIconLoader.addIconView(iconView);
							//制御用にiconを保持
							adIconViewArray.add(iconView);
						}

						WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams();
						mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
						mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
						mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
						mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
						mLayoutParams.gravity = Gravity.TOP;
						mLayoutParams.format = PixelFormat.TRANSLUCENT;
						mWm.addView(mBaseLayout, mLayoutParams);
					}
				}
			}
		});
	}
	
	public static void createIconViewTop(){
		createIconViewTop(ICON_DISPLAY_COUNT);
	}
	
	public static void createIconViewBottom(){
		createIconViewBottom(ICON_DISPLAY_COUNT);
	}

	public static void loadIconLoader() {

		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					mIconLoader.loadAd();
				}	
			}
		});
	}
	
	public static void hideIconView(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					for(int i =0 ; i < adIconViewArray.size() ; i++){
						NendAdIconView iconView = adIconViewArray.get(i);
						iconView.setVisibility(View.GONE);
					}
				}
				if(mBaseLayout != null){
					mBaseLayout.setVisibility(View.GONE);
				}
			}
		});
	}

	public static void showIconView(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					for(int i =0 ; i < adIconViewArray.size() ; i++){
						NendAdIconView iconView = adIconViewArray.get(i);
						iconView.setVisibility(View.VISIBLE);
					}
				}
				if(mBaseLayout != null){
					mBaseLayout.setVisibility(View.VISIBLE);
				}
			}
		});
	}

	public static void pauseIconView(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					mIconLoader.pause();
				}
			}
		});
	}

	public static void resumeIconView(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					mIconLoader.resume();
				}
			}
		});
	}
	
	// 解放
	public static void releaseIconView(){
		
		hideIconView();
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {
				if(mIconLoader != null){
					mIconLoader = null;
				}
				if(adIconViewArray != null){
					adIconViewArray.clear();
					adIconViewArray = null;
				}
				if(mBaseLayout != null){
					mBaseLayout.removeAllViews();
				}
				if(mWm != null && mBaseLayout != null){
					mWm.removeView(mBaseLayout);
					mBaseLayout = null;
				}
				if(mWm != null){
					mWm = null;
				}
			}
		});
	}

	private static OnReceiveListener sOnReceiveListener = new OnReceiveListener() {
		
		@Override
		public void onReceiveAd(NendAdIconView iconView) {
			NendIconModule.onReceiveIconAd();
		}
	};

	private static OnClickListener sOnClickListener = new OnClickListener() {
		
		@Override
		public void onClick(NendAdIconView iconView) {
			NendIconModule.onClickIconAd();
		}
	};

	private static OnFailedListener sOnFailedListener = new OnFailedListener() {
		
		@Override
		public void onFailedToReceiveAd(NendIconError iconError) {
			NendIconModule.onFailedIconAd();
		}
	};

	public static native void onReceiveIconAd();
	public static native void onFailedIconAd();
	public static native void onClickIconAd();
}

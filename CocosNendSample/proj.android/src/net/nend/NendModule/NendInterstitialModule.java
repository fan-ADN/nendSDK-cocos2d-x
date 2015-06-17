package net.nend.NendModule;

import net.nend.android.NendAdInterstitial;
import net.nend.android.NendAdInterstitial.NendAdInterstitialClickType;
import net.nend.android.NendAdInterstitial.NendAdInterstitialShowResult;
import net.nend.android.NendAdInterstitial.NendAdInterstitialStatusCode;

import org.cocos2dx.cpp.AppActivity;
import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;

public class NendInterstitialModule {	
	
	private static int mSelectedInterstitialType = 0;
	public static final int NO_BACK_KEY_SHOW_INTERSTITIAL        = 0;  // backキー以外でインタースティシャル表示
	public static final int ON_BACK_KEY_SHOW_NORMAL_INTERSTITIAL = 1;  // backキーで通常のインタースティシャル表示
	public static final int ON_BACK_KEY_SHOW_FINISH_INTERSTITIAL = 2;  // backキーで終了時のインタースティシャル表示
	
	private static String useSpotIdForShowFinishAd = null;
	
	// クリックイベントのタイプが返却される
	public static NendAdInterstitial.OnClickListener setOnClickListener(){
		
		NendAdInterstitial.OnClickListener listener = new NendAdInterstitial.OnClickListener() {
			
			@Override
			public void onClick(NendAdInterstitialClickType clickType) {
				int resultCode = clickType.ordinal();
				onClickStatus(resultCode);
			}
		};
		return listener;
	}
	
	// クリックイベントのタイプとspotIDが返却される
	public static NendAdInterstitial.OnClickListener setOnClickListenerWithSpotId(){
		
		NendAdInterstitial.OnClickListener listener = new NendAdInterstitial.OnClickListenerSpot() {
			
			@Override
			public void onClick(NendAdInterstitialClickType clickType) {
				// ここの通知は呼び出されない
			}
			
			@Override
			public void onClick(NendAdInterstitialClickType clickType, int spotId) {
				int resultCode = clickType.ordinal();
				onClickStatusWithSpotId(resultCode, spotId);
			}
		};
		return listener;
	}
	
	// ロード結果が返却される
	public static void createInterstitialAd(final String apiKey, final String spotID){
		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		activity.runOnUiThread(new Runnable() {
			public void run() {

				int intSpotID = Integer.parseInt(spotID);
				
				NendAdInterstitial.loadAd(activity, apiKey, intSpotID);
				
				// 広告のロード結果とspotIDの通知を受け取るリスナーを設定する
				NendAdInterstitial.OnCompletionListener listenerWithSpotId = new NendAdInterstitial.OnCompletionListenerSpot() {
					
					@Override
					public void onCompletion(NendAdInterstitialStatusCode statusCode) {
						// ここの通知は呼び出されない
					}
					@Override
					public void onCompletion(NendAdInterstitialStatusCode statusCode, int spotId) {
						int resultCode = statusCode.ordinal();
						loadResultStatus(resultCode);	
						loadResultStatusWithSpotId(resultCode, spotId);
					}
				};
				NendAdInterstitial.setListener(listenerWithSpotId);
			}
		});
	}
	
	public static void showInterstitial(final String spotID){
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		
		if (AppActivity.isBackKeySelected()){			

			// backキーでshowInterstitialViewが呼ばれたとき
			mSelectedInterstitialType = ON_BACK_KEY_SHOW_NORMAL_INTERSTITIAL;
		
		}else{			
			
			// backキー以外でshowInterstitialViewが呼ばれた時
			mSelectedInterstitialType = NO_BACK_KEY_SHOW_INTERSTITIAL;
			
			activity.runOnUiThread(new Runnable() {
				public void run() {
					
					if (spotID == null){
						
						NendAdInterstitial.OnClickListener listener = setOnClickListener();
						resultOfShowAd(activity, listener);
 
					}else{
						
						NendAdInterstitial.OnClickListener listener = setOnClickListenerWithSpotId();
						resultOfShowAdWithSpotId(activity, spotID, listener);
 
					}
               
				}
			});
		}
	}
	
	public static void showFinishInterstitial(){
		
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		
		if (AppActivity.isBackKeySelected()){			
			
			// backキーでshowFinishNADInterstitialViewが呼ばれたとき
			mSelectedInterstitialType = ON_BACK_KEY_SHOW_FINISH_INTERSTITIAL;
		
		}else{			
			
			// backキー以外でshowFinishNADInterstitialViewが呼ばれた時
			mSelectedInterstitialType = NO_BACK_KEY_SHOW_INTERSTITIAL;
			
			activity.runOnUiThread(new Runnable() {
				public void run() {
					
					if (useSpotIdForShowFinishAd == null){
						
						NendAdInterstitial.OnClickListener listener = setOnClickListener();
						resultOfshowFinishAd(activity, listener);
		                
					}else{
						
						NendAdInterstitial.OnClickListener listener = setOnClickListenerWithSpotId();
						resultOfshowFinishAdWithSpotId(activity, useSpotIdForShowFinishAd, listener);	
					}
				}
			});
		}
	}
	
	// バックキーでインタースティシャルの表示が呼ばれた場合
	public static void showNADInterstitialViewFromBackKey(){

		final Activity activity = (Activity)Cocos2dxActivity.getContext();

		switch (mSelectedInterstitialType){
		case 1: // 通常広告
			
			activity.runOnUiThread(new Runnable() {
				public void run() {
					
					if(useSpotIdForShowFinishAd == null){
						
						NendAdInterstitial.OnClickListener listener = setOnClickListener();
						resultOfShowAd(activity, listener);
						
					}else{
						
						NendAdInterstitial.OnClickListener listener = setOnClickListenerWithSpotId();
						resultOfShowAdWithSpotId(activity, useSpotIdForShowFinishAd, listener);
					}
				}
			});
		case 2: // 終了時広告
			
			activity.runOnUiThread(new Runnable() {
				public void run() {

					if(useSpotIdForShowFinishAd == null){
					
						NendAdInterstitial.OnClickListener listener = setOnClickListener();
						resultOfshowFinishAd(activity, listener);
		                
					}else{
						
						NendAdInterstitial.OnClickListener listener = setOnClickListenerWithSpotId();
						resultOfshowFinishAdWithSpotId(activity, useSpotIdForShowFinishAd, listener);
					}
				}
			});			
		}
		
		mSelectedInterstitialType = NO_BACK_KEY_SHOW_INTERSTITIAL;
		AppActivity.setBackKeySelected(false);
	}
	
	// インタースティシャル広告の生成
	public static void createInterstitial(final String apiKey, final String spotID) {
		createInterstitialAd(apiKey, spotID);
	}
	
	// インタースティシャル広告の表示
	public static void showInterstitialView() {
		showInterstitial(null);
	}
	
	// インタースティシャル広告の表示(spotID指定あり)
	public static void showInterstitialView(final String spotID) {		
		showInterstitial(spotID);
	}
	
	// インタースティシャル広告の削除
	public static void dismissNADInterstitialView(){
		final Activity activity = (Activity)Cocos2dxActivity.getContext();
		activity.runOnUiThread(new Runnable() {
			public void run() {
				
				boolean dismissResult = NendAdInterstitial.dismissAd();
                // 広告削除結果で何かの処理する場合
				if (dismissResult){
					mSelectedInterstitialType = NO_BACK_KEY_SHOW_INTERSTITIAL;
				}
			}
		});
	}
	
	// 終了時広告表示
	public static void showFinishNADInterstitialView(){
        useSpotIdForShowFinishAd = null;  
        showFinishInterstitial();
	}
	
	// 終了時広告表示(spotID指定あり)
	public static void showFinishNADInterstitialView(final String spotID){
		useSpotIdForShowFinishAd = spotID;
		showFinishInterstitial();
	}
	
	public static void resultOfShowAd(Activity activity, NendAdInterstitial.OnClickListener listener){
        // 表示結果が返却される				
        NendAdInterstitialShowResult result = NendAdInterstitial.showAd(activity, listener);
        int resultCode = result.ordinal();
        showResultStatus(resultCode);
	}
	
	public static void resultOfShowAdWithSpotId(Activity activity, final String spotID, NendAdInterstitial.OnClickListener listener){
        // 表示結果が返却される			
		int intSpotId = Integer.parseInt(spotID);
        NendAdInterstitialShowResult result = NendAdInterstitial.showAd(activity, intSpotId, listener);
        int resultCode = result.ordinal();
        showResultStatusWithSpotId(resultCode, intSpotId);	
	}
	
	public static void resultOfshowFinishAd(Activity activity, NendAdInterstitial.OnClickListener listener){
		// 終了時広告の表示結果が返却される
		NendAdInterstitialShowResult result = NendAdInterstitial.showFinishAd(activity, listener);	
        int resultCode = result.ordinal();
        showResultStatus(resultCode);	
	}
	
	public static void resultOfshowFinishAdWithSpotId(Activity activity, final String spotID, NendAdInterstitial.OnClickListener listener){
		// 終了時広告の表示結果が返却される
		int intSpotId = Integer.parseInt(spotID);
		NendAdInterstitialShowResult result = NendAdInterstitial.showFinishAd(activity, intSpotId, listener);	
        int resultCode = result.ordinal();
        showResultStatusWithSpotId(resultCode, intSpotId);	
	}
	
	public static native void loadResultStatus(final int statusCode);
	public static native void loadResultStatusWithSpotId(final int statusCode, final int spotId);
	public static native void showResultStatus(final int statusCode);
	public static native void showResultStatusWithSpotId(final int statusCode, final int spotId);
	public static native void onClickStatus(final int statusCode);
	public static native void onClickStatusWithSpotId(final int statusCode, final int spotId);	
}

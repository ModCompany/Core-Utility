package com.core.api.module.moduleapi.filesytem;

import com.core.api.JsHelper;
import com.zhekasmirnov.innercore.utils.UIUtils;

import android.app.Activity;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Base64;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

import org.json.JSONObject;

public class GitHubFileSystem extends LocalFileSystem {
    private String autor, repository;

    public static boolean isConnection(){
        Activity context = UIUtils.getContext();
        ConnectivityManager connectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (connectivityManager != null) {
            NetworkInfo activeNetworkInfo = connectivityManager.getActiveNetworkInfo();
            return activeNetworkInfo != null && activeNetworkInfo.isConnected();
        }
        return false;
    }

    public static String sendHttp(String http){
        String result = "";
        HttpURLConnection urlConnection = null;
        try {
            URL url = new URL(http);
            urlConnection = (HttpURLConnection) url.openConnection();
            InputStream inputStream = urlConnection.getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                result += line;
            }
            return result;
        } catch (Exception e) {
            JsHelper.log("error getFile Github");
            JsHelper.error(e);
        }
        if (urlConnection != null) {
            urlConnection.disconnect();
        }
        return null;
        
    }

    public static String parseBase64String(String text){
        String result = "";
		try{
			String[] array = text.split("\\n");
			for(String line : array)
				result += new String(Base64.decode(new String(line).getBytes(), Base64.DEFAULT));
		}catch(Exception e){
            JsHelper.log("error parseBase64String Github");
            JsHelper.error(e);
            return null;
        }
		return result;
    }


    public GitHubFileSystem(String autor, String repository, String directory){
        this.autor = autor;
        this.repository = repository;
        this.directory = directory;
    }

    @Override
    public String getFile(String path) {
        String file = sendHttp("https://api.github.com/repos/"+autor+"/"+repository+"/contents/"+(directory == null ? path : directory + "/" + path)+"?ref=main");
        if(file == null) return null;
        try {
            JSONObject json = new JSONObject(file);
            if(json.isNull("content")) return null;
            return parseBase64String(json.getString("content"));
        } catch (Exception e) {
            JsHelper.log("error getFile Github");
            JsHelper.error(e);
        }
        return null;
    }
}

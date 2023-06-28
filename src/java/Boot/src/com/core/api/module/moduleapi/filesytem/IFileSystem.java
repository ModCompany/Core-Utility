package com.core.api.module.moduleapi.filesytem;

import org.json.JSONArray;
import org.json.JSONObject;

public interface IFileSystem {
    String getFile(String path);
    JSONObject parseJSONObject(String path);
    JSONArray parseJSONArray(String path);
}

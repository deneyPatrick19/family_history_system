package com.example.family_history_system.common.response;

import com.fasterxml.jackson.annotation.JsonAnyGetter;
import com.fasterxml.jackson.annotation.JsonInclude;
import lombok.Data;

import java.util.LinkedHashMap;
import java.util.Map;

@Data
@JsonInclude(JsonInclude.Include.NON_NULL)
public class Response {
    private boolean success;
    private String message;
    private Object data;
    private Map<String, Object> extra = new LinkedHashMap<>();

    public static Response buildSuccess() {
        Response r = new Response();
        r.setSuccess(true);
        return r;
    }

    public static Response buildSuccess(Object data) {
        Response r = new Response();
        r.setSuccess(true);
        r.setData(data);
        return r;
    }

    public static Response buildSuccess(String message, Object data) {
        Response r = new Response();
        r.setSuccess(true);
        r.setMessage(message);
        r.setData(data);
        return r;
    }

    public static Response buildFault(String message) {
        Response r = new Response();
        r.setSuccess(false);
        r.setMessage(message);
        return r;
    }

    public static Response buildFault() {
        Response r = new Response();
        r.setSuccess(false);
        return r;
    }

    public Response withExtra(String key, Object value) {
        this.extra.put(key, value);
        return this;
    }

    @JsonAnyGetter
    public Map<String, Object> getExtraFields() {
        return extra;
    }
}

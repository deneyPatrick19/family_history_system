package com.example.family_history_system.entity;
import lombok.Data;
import java.util.Map;

@Data
public class Response {
    private String status;
    private String msg;
    private Map<String, Object> data;

    public static Response buildSuccess(Map<String, Object> data){
        Response responseBody = new Response();
        responseBody.setStatus("200");
        responseBody.setMsg("success");
        responseBody.setData(data);
        return responseBody;
    }
    
    public static Response buildFault(){
        Response responseBody = new Response();
        responseBody.setStatus("400");
        responseBody.setMsg("failure");
        return responseBody;
    }
}

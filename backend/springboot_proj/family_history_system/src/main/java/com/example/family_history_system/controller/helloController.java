package com.example.family_history_system.controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMethod;

@RestController
public class helloController {
    @RequestMapping(value="/hello",method=RequestMethod.GET)
    public String hello(){
        return "Hello World";
    }

    @RequestMapping(value = "/login",method = RequestMethod.GET)
    //localhost:8080/login?username=xia&password=123
    public String log(String username, String password) {
        return username + ":" + password;
    }
}

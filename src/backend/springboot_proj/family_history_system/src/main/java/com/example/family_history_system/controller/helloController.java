package com.example.family_history_system.controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class helloController {

    /**
     * 返回一个文本信息---String
     */
    @GetMapping("/hello")
    public String method() {
        return "Hello World";
    }
}

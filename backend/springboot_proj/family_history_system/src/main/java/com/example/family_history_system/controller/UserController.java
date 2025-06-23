package com.example.family_history_system.controller;

import com.example.family_history_system.service.UserService;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import com.example.family_history_system.entity.User;
import java.util.List;

@CrossOrigin
@RestController
@ResponseBody
@RequestMapping("/user")
public class UserController {
    @Autowired
    private UserService userService;

    @PostMapping("/signup")
    public int signup(@RequestBody User user){
        if (userService.findByUsername(user.getUsername())==null){
            return userService.insert(user);
        }
        return 0;
    }

    @PostMapping("/update")
    public int update(@RequestBody User user){
        return userService.update(user);
    }

    @PostMapping("/delete")
    public int delete(@RequestParam Integer id){
        return userService.delete(id);
    }

    @PostMapping("/find")
    public User find(@RequestParam Integer id){
        return userService.findById(id);
    }

    @GetMapping("/findall")
    public List<User> findAll(){
        return userService.findAll();
    }

    @PostMapping("/login")
    public Boolean login(@Param("username") String username, @Param("password")  String password) {
        return userService.verifyUser(username, password);
    }
}

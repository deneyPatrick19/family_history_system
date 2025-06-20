package com.example.family_history_system.controller;

import com.example.family_history_system.service.IUserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import com.example.family_history_system.entity.User;
import java.util.List;


@RestController
@RequestMapping("/user")
public class UserController {
    @Autowired
    private IUserService userService;

    @GetMapping
    public List<User> findAll(){
        return userService.list();
    }

    @GetMapping("/{id}")
    public User findById(@PathVariable Integer id){
        return userService.getById(id);
    }

    @PostMapping
    public Boolean add(@RequestBody User user){
        return userService.saveOrUpdate(user);
    }

    @DeleteMapping("/delete/{id}")
    public Boolean delete(@PathVariable Integer id){
        return userService.removeById(id);
    }
}

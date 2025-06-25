package com.example.family_history_system.controller;
import com.example.family_history_system.entity.Response;
import com.example.family_history_system.entity.JwtUtil;
import com.example.family_history_system.service.UserService;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import com.example.family_history_system.entity.User;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

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
    public Response login(@Param("username") String username, @Param("password")  String password) {
        Boolean result =  userService.verifyUser(username, password);
        if (result){
            // 生成JWT token
            String token = JwtUtil.generateToken(username);
            
            // 创建返回数据，包含token和用户信息
            Map<String, Object> data = new HashMap<>();
            data.put("token", token);
            data.put("username", username);
            
            return Response.buildSuccess(data);
        }
        return Response.buildFault();
    }
}

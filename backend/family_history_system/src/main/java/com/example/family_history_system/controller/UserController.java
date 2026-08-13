package com.example.family_history_system.controller;
import com.example.family_history_system.common.response.Response;
import com.example.family_history_system.common.util.JwtUtil;
import com.example.family_history_system.service.UserService;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import com.example.family_history_system.entity.User;
import java.util.HashMap;
import java.util.Map;

@CrossOrigin
@RestController
@ResponseBody
@RequestMapping("/user")
public class UserController {
    @Autowired
    private UserService userService;

    @Autowired
    private JwtUtil jwtUtil;

    @PostMapping("/signup")
    public Response signup(@RequestBody User user){
        if (userService.findByUsername(user.getUsername())==null){
            boolean res = userService.signUp(user);
            return res ? Response.buildSuccess("注册成功", user) : Response.buildFault("注册失败");
        }
        return Response.buildFault("用户名已存在");
    }

    @PostMapping("/update")
    public Response update(@RequestBody User user){
        boolean res = userService.updateUser(user);
        return res ? Response.buildSuccess("更新用户成功", user) : Response.buildFault("更新用户失败");
    }

    @PostMapping("/delete")
    public Response delete(@RequestParam Integer id){
        boolean res = userService.removeById(id);
        return res ? Response.buildSuccess("删除用户成功") : Response.buildFault("删除用户失败");
    }

    @PostMapping("/find")
    public Response find(@RequestParam Integer id){
        User user = userService.findById(id);
        return user != null ? Response.buildSuccess("获取用户成功", user) : Response.buildFault("用户不存在");
    }

    @GetMapping("/findall")
    public Response findAll(){
        return Response.buildSuccess("获取所有用户成功", userService.findAll());
    }

    @PostMapping("/login")
    public Response login(@Param("username") String username, @Param("password")  String password) {
        Boolean result =  userService.verifyUser(username, password);
        if (result){
            // 查询用户实体获取 id
            User user = userService.findByUsername(username);

            // 生成JWT token
            String token = jwtUtil.generateToken(username);

            // 创建返回数据，包含token和用户信息
            Map<String, Object> data = new HashMap<>();
            data.put("token", token);
            data.put("username", username);
            data.put("id", user.getId());

            return Response.buildSuccess("登录成功", data);
        }
        return Response.buildFault("登录失败");
    }
}

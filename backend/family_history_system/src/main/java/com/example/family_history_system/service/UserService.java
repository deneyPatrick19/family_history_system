package com.example.family_history_system.service;
import com.baomidou.mybatisplus.extension.service.IService;
import com.example.family_history_system.entity.User;
import java.util.List;

public interface UserService extends IService<User> {
    Boolean verifyUser(String username, String password);
    Boolean signUp(User user);
    Boolean updateUser(User user);
    User findByUsername(String username);
    User findById(int id);
    List<User> findAll();
}

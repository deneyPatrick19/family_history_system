package com.example.family_history_system.service;
import com.example.family_history_system.entity.User;
import java.util.List;

public interface UserService {
    int insert(User user);
    int update(User user);
    int delete(Integer id);
    User findById(Integer id);
    List<User> findAll();
    Boolean verifyUser(String username, String password);
    User findByUsername(String username);
}

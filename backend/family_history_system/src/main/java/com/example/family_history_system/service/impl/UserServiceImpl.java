package com.example.family_history_system.service.impl;

import com.example.family_history_system.entity.User;
import com.example.family_history_system.mapper.UserMapper;
import com.example.family_history_system.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import sun.text.normalizer.IntTrie;

import java.util.List;

@Service
public class UserServiceImpl implements UserService {
    @Autowired
    private UserMapper userMapper;

    public int insert(User user){
        return userMapper.insert(user);
    }
    public int update(User user){
        return userMapper.updateById(user);
    }
    public int delete(Integer id){
        return userMapper.deleteById(id);
    }
    public User findById(Integer id){
        return userMapper.selectById(id);
    }
    public List<User> findAll(){
        return  userMapper.findAll();
    }
    public Boolean verifyUser(String username, String password){
        User User2 = userMapper.findByUsername(username);
        if (User2 == null) {
            return false;
        }else {
            return password.equals(User2.getPassword());
        }
    }
    public User findByUsername(String username){
        return userMapper.findByUsername(username);
    }
}

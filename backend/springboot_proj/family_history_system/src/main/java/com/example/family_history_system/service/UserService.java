package com.example.family_history_system.service;

import com.example.family_history_system.mapper.UserMapper;
import com.example.family_history_system.entity.User;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

@Service
public class UserService extends ServiceImpl<UserMapper,User>{
}

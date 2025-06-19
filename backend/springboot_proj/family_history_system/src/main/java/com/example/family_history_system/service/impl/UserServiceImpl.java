package com.example.family_history_system.service.impl;

import com.example.family_history_system.entity.User;
import com.example.family_history_system.mapper.UserMapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;
import com.example.family_history_system.service.IUserService;

@Service("userServiceImpl")
public class UserServiceImpl extends ServiceImpl<UserMapper,User> implements IUserService {
}

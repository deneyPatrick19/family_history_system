package com.example.family_history_system.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.family_history_system.common.util.PasswordUtil;
import com.example.family_history_system.entity.User;
import com.example.family_history_system.mapper.UserMapper;
import com.example.family_history_system.service.UserService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserServiceImpl extends ServiceImpl<UserMapper, User> implements UserService {

    /**
     * 校验用户登录凭据
     * @param username 用户名
     * @param password 明文密码
     * @return true 密码匹配；false 用户不存在或密码不匹配
     */
    @Override
    public Boolean verifyUser(String username, String password){
        User user = findByUsername(username);
        if (user == null) {
            return false;
        }else {
            return PasswordUtil.matches(password, user.getPassword());
        }
    }

    /**
     * 用户注册：密码 BCrypt 哈希后入库
     * @param user 待注册用户（含明文密码）
     * @return true 注册成功
     */
    @Override
    public Boolean signUp(User user){
        user.setPassword(PasswordUtil.encode(user.getPassword()));
        return this.save(user);
    }

    /**
     * 更新用户密码：新密码 BCrypt 哈希后更新
     * @param user 含用户名与新明文密码
     * @return true 更新成功；false 用户不存在或新旧密码相同
     */
    @Override
    public Boolean updateUser(User user){
        User res = this.findByUsername(user.getUsername());
        if (res == null) {
            return false;
        } else if (PasswordUtil.matches(user.getPassword(), res.getPassword())) {
            return false;
        } else {
            res.setPassword(PasswordUtil.encode(user.getPassword()));
            return this.updateById(res);
        }
    }

    /**
     * 按用户名查询用户
     * @param username 用户名
     * @return 用户实体；不存在返回 null
     */
    @Override
    public User findByUsername(String username){
        return this.getOne(new LambdaQueryWrapper<User>().eq(User::getUsername,username));
    }

    /**
     * 按主键查询用户
     * @param id 用户ID
     * @return 用户实体；不存在返回 null
     */
    @Override
    public User findById(int id){
        return this.getOne(new LambdaQueryWrapper<User>().eq(User::getId,id));
    }

    /**
     * 查询全部用户
     * @return 用户列表
     */
    @Override
    public List<User> findAll(){
        return this.list(new LambdaQueryWrapper<>());
    }
}

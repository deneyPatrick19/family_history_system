package com.example.family_history_system.entity;

//import com.baomidou.mybatisplus.annotation.TableName;
//import com.baomidou.mybatisplus.annotation.IdType;
//import com.baomidou.mybatisplus.annotation.TableId;
//import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
//@TableName(value = "user")
public class User {
//    @ApiModelProperty("用户名")
    private String username;
//    @ApiModelProperty("密码")
    private String password;
}

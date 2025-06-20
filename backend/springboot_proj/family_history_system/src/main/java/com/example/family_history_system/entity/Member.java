package com.example.family_history_system.entity;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.util.Date;

@Data
@TableName(value = "member")
public class Member {
    @TableId(value = "id")
    private Integer id;
    private Integer family_table_id;
    private String name;
    private String gender;
    private Date birthdate;
    private Date deathdate;
    private String icon;
}

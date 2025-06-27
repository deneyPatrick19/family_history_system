package com.example.family_history_system.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.util.Date;

@Data
@TableName("family_table")
public class Family_table {
    @TableId(value = "id",type = IdType.AUTO)
    private Integer id;
    private Integer user_id;
    private String table_name;
    private String content;
    private Date establish_time;
}

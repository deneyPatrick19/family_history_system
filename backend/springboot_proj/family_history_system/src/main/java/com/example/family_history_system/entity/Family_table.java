package com.example.family_history_system.entity;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.util.Date;

@Data
@TableName("family_table")
public class Family_table {
    @TableId("id")
    private Integer id;
    private Integer member_id;
    private String table_name;
    private String content;
    private Date establish_time;
}

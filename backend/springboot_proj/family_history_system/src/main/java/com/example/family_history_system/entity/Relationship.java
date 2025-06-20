package com.example.family_history_system.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import com.github.jeffreyning.mybatisplus.anno.MppMultiId;

import lombok.Data;

@Data
@TableName(value = "relationship")
public class Relationship {
    @MppMultiId
    @TableField("member_id1")
    private int member_id1;
    @MppMultiId
    @TableField("member_id2")
    private int member_id2;
    private String relation;
}

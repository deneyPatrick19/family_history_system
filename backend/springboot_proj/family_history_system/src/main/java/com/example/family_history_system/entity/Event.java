package com.example.family_history_system.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.util.Date;

@Data
@TableName(value = "event")
public class Event {
    @TableId("member_id")
    private Integer member_id;
    private Date event_date;
    private String event_type;
    private String event_description;
    private String event_file;
}

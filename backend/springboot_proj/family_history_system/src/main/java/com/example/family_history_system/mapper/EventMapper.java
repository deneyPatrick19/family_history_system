package com.example.family_history_system.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Event;
import org.apache.ibatis.annotations.*;
import org.apache.ibatis.type.JdbcType;

import java.lang.annotation.Inherited;
import java.util.List;

@Mapper
public interface EventMapper extends BaseMapper<Event> {

    @Select("select * from `system`.event")
    @Results({
            @Result(property = "member_id", column = "member_id", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "event_date", column = "event_date", id = true,jdbcType = JdbcType.DATE),
            @Result(property = "event_type", column = "event_type", jdbcType = JdbcType.VARCHAR),
            @Result(property = "event_description", column = "event_description", jdbcType = JdbcType.VARCHAR),
            @Result(property = "event_file", column = "event_file", jdbcType = JdbcType.VARCHAR)
    })
    List<Event> findAllEvent();

    @Insert("insert into `system`.event(member_id, event_date, event_type, event_description, event_file) VALUES (#{member_id}, #{event_date}, #{event_type}, #{event_description}, #{event_file})")
    @Results({
            @Result(property = "member_id", column = "member_id", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "event_date", column = "event_date", jdbcType = JdbcType.DATE),
            @Result(property = "event_type", column = "event_type", jdbcType = JdbcType.VARCHAR),
            @Result(property = "event_description", column = "event_description", jdbcType = JdbcType.VARCHAR),
            @Result(property = "event_file", column = "event_file", jdbcType = JdbcType.VARCHAR)
    })
    int add(Event event);
}

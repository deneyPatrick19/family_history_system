package com.example.family_history_system.mapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Event;
import org.apache.ibatis.annotations.*;
import org.apache.ibatis.type.JdbcType;
import java.util.List;

@Mapper
public interface EventMapper extends BaseMapper<Event> {

    @Select("select * from `system`.event")
    @Results({
            @Result(property = "id", column = "id", id = true, jdbcType = JdbcType.INTEGER),
            @Result(property = "member_id", column = "member_id", jdbcType = JdbcType.INTEGER),
            @Result(property = "event_date", column = "event_date", jdbcType = JdbcType.DATE),
            @Result(property = "event_type", column = "event_type", jdbcType = JdbcType.VARCHAR),
            @Result(property = "event_description", column = "event_description", jdbcType = JdbcType.VARCHAR),
    })
    List<Event> findAllEvent();

    @Select("select * from `system`.event where member_id = #{memberId}")
    @Results({
            @Result(property = "id", column = "id", id = true, jdbcType = JdbcType.INTEGER),
            @Result(property = "member_id", column = "member_id", jdbcType = JdbcType.INTEGER),
            @Result(property = "event_date", column = "event_date", jdbcType = JdbcType.DATE),
            @Result(property = "event_type", column = "event_type", jdbcType = JdbcType.VARCHAR),
            @Result(property = "event_description", column = "event_description", jdbcType = JdbcType.VARCHAR),
    })
    List<Event> findByMemberId(Integer memberId);

    @Delete("delete from `system`.event where member_id = #{memberId}")
    int deleteByMemberId(@Param("memberId") Integer memberId);

    @Delete("delete from `system`.event where member_id in (select id from `system`.member where family_table_id = #{familyTableId})")
    int deleteByFamilyTableId(@Param("familyTableId") Integer familyTableId);
}

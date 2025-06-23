package com.example.family_history_system.mapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Family_table;
import org.apache.ibatis.annotations.*;
import org.apache.ibatis.type.JdbcType;
import java.util.List;

@Mapper
public interface Family_tableMapper extends BaseMapper<Family_table> {
    @Select("select * from `system`.family_table")
    @Results({
            @Result(property = "id", column = "id", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "user_id", column = "user_id", jdbcType = JdbcType.INTEGER),
            @Result(property = "table_name", column = "table_name", jdbcType = JdbcType.VARCHAR),
            @Result(property = "content", column = "content", jdbcType = JdbcType.VARCHAR),
            @Result(property = "establish_time", column = "establish_time", jdbcType = JdbcType.DATE)
    })
    List<Family_table> FindAllFamilyTable();
}

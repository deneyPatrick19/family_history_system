package com.example.family_history_system.mapper;
import com.example.family_history_system.entity.User;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.*;
import org.apache.ibatis.type.JdbcType;
import java.util.List;

@Mapper
public interface UserMapper extends BaseMapper<User> {

    @Select("select * from `system`.user ")
    @Results({
            @Result(property = "id", column = "id", jdbcType = JdbcType.INTEGER, id = true),
            @Result(property = "username", column = "username", jdbcType = JdbcType.VARCHAR),
            @Result(property = "password", column = "password", jdbcType = JdbcType.VARCHAR),
    })
    List<User> findAll();

    @Select("select * from `system`.user where username = #{username}")
    @Results({
            @Result(property = "id", column = "id", jdbcType = JdbcType.INTEGER, id = true),
            @Result(property = "username", column = "username", jdbcType = JdbcType.VARCHAR),
            @Result(property = "password", column = "password", jdbcType = JdbcType.VARCHAR),
    })
    User findByUsername(@Param("username") String username);
}

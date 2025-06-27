package com.example.family_history_system.mapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Member;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Result;
import org.apache.ibatis.annotations.Results;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.type.JdbcType;
import java.util.List;

@Mapper
public interface MemberMapper extends BaseMapper<Member> {
    @Select("select * from `system`.member")
    @Results({
            @Result(property = "id", column = "id", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "family_table_id", column = "family_table_id", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "name", column = "name", jdbcType = JdbcType.VARCHAR),
            @Result(property = "birthdate", column = "birthdate", jdbcType = JdbcType.DATE),
            @Result(property = "deathdate", column = "deathdate", jdbcType = JdbcType.DATE),
            @Result(property = "icon", column = "icon", jdbcType = JdbcType.VARCHAR),
    })
    List<Member> selectAllMember();
    
    @Select("select * from `system`.member where family_table_id = #{familyTableId}")
    @Results({
            @Result(property = "id", column = "id", id = true,jdbcType = JdbcType.INTEGER),
            @Result(property = "family_table_id", column = "family_table_id", jdbcType = JdbcType.INTEGER),
            @Result(property = "name", column = "name", jdbcType = JdbcType.VARCHAR),
            @Result(property = "gender", column = "gender", jdbcType = JdbcType.VARCHAR),
            @Result(property = "birthdate", column = "birthdate", jdbcType = JdbcType.DATE),
            @Result(property = "deathdate", column = "deathdate", jdbcType = JdbcType.DATE),
            @Result(property = "icon", column = "icon", jdbcType = JdbcType.VARCHAR),
    })
    List<Member> selectByFamilyTableId(Integer familyTableId);

    @Delete("delete from `system`.member where family_table_id = #{familyTableId}")
    int deleteByFamilyTableId(@Param("familyTableId") Integer familyTableId);
}

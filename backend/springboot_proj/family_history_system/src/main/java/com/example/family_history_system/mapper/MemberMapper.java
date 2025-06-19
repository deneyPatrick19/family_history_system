package com.example.family_history_system.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.example.family_history_system.entity.Member;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface MemberMapper extends BaseMapper<Member> {
    @Select("select * from member")
    List<Member> selectAllMember();
}

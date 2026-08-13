package com.example.family_history_system.service.impl;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.family_history_system.entity.Member;
import com.example.family_history_system.mapper.MemberMapper;
import com.example.family_history_system.service.MemberService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class MemberServiceImpl extends ServiceImpl<MemberMapper, Member> implements MemberService {

    /**
     * 查询全部成员
     * @return 成员列表
     */
    @Override
    public List<Member> findAll(){
        return this.list(new LambdaQueryWrapper<>());
    }

    /**
     * 根据id查询成员
     * @return 单个成员
     */
    @Override
    public Member findById(Integer id){
        return this.getById(id);
    }

    /**
     * 按家族表ID查询其下全部成员
     * @param familyTableId 家族表ID
     * @return 成员列表
     */
    @Override
    public List<Member> findByFamilyTableId(Integer familyTableId){
        return this.list(new LambdaQueryWrapper<Member>().eq(Member::getFamily_table_id, familyTableId));
    }
}

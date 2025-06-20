package com.example.family_history_system.service.impl;
import com.example.family_history_system.entity.Member;
import com.example.family_history_system.mapper.MemberMapper;
import com.example.family_history_system.service.MemberService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class MemberServiceImpl implements MemberService {

    @Autowired
    private MemberMapper memberMapper;

    public int insertMember(Member member){
        return memberMapper.insert(member);
    }
    public int updateMember(Member member) {
        return memberMapper.updateById(member);
    }
    public int deleteMember(Integer id) {
        return memberMapper.deleteById(id);
    }
    public Member findById(Integer id){
        return memberMapper.selectById(id);
    }
    public List<Member> findAll(){
        return memberMapper.selectAllMember();
    }
}

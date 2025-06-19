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

    public void insertMember(Member member){
        memberMapper.insert(member);
    }
    public void updateMember(Member member) {
        memberMapper.updateById(member);
    }
    public void deleteMember(Integer id) {
        memberMapper.deleteById(id);
    }
    public void findById(Integer id){
        memberMapper.selectById(id);
    }
    public List<Member> findAll(){
        return memberMapper.selectAllMember();
    }
}

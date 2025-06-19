package com.example.family_history_system.service;

import com.example.family_history_system.entity.Member;

import java.util.List;

public interface MemberService {
    void insertMember(Member member);
    void updateMember(Member member);
    void deleteMember(Integer id);
    void findById(Integer id);
    List<Member> findAll();
}

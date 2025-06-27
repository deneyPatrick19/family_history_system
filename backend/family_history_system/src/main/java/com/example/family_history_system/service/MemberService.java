package com.example.family_history_system.service;
import com.example.family_history_system.entity.Member;
import java.util.List;

public interface MemberService {
    int insertMember(Member member);
    int updateMember(Member member);
    int deleteMember(Integer id);
    Member findById(Integer id);
    List<Member> findAll();
    List<Member> findByFamilyTableId(Integer familyTableId);
}

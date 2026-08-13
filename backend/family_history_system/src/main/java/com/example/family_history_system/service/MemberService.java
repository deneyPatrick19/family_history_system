package com.example.family_history_system.service;
import com.baomidou.mybatisplus.extension.service.IService;
import com.example.family_history_system.entity.Member;
import java.util.List;

public interface MemberService extends IService<Member> {
    List<Member> findAll();
    Member findById(Integer id);
    List<Member> findByFamilyTableId(Integer familyTableId);
}

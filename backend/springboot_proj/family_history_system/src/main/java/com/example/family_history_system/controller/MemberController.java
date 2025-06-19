package com.example.family_history_system.controller;

import com.example.family_history_system.entity.Member;
import com.example.family_history_system.service.MemberService;
import io.swagger.models.auth.In;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/member")
public class MemberController {
    @Autowired
    private MemberService memberService;

    @PostMapping("/add")
    public Integer insertMember(@RequestBody Member member){
        memberService.insertMember(member);
        return member.getId();
    }
    @PostMapping("/change")
    public Integer updateMember(@RequestBody Member member){
        memberService.updateMember(member);
        return member.getId();
    }
    @PostMapping("/delete")
    public Integer deleteMember(@RequestBody Member member){
        memberService.deleteMember(member.getId());
        return member.getId();
    }
    @PostMapping("/find")
    public Integer findById(@RequestBody Member member){
        memberService.findById(member.getId());
        return member.getId();
    }

    @GetMapping("/findall")
    public List<Member> findAll(){
        return memberService.findAll();
    }
}

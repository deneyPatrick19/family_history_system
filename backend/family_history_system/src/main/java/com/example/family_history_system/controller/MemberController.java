package com.example.family_history_system.controller;
import com.example.family_history_system.entity.Member;
import com.example.family_history_system.service.MemberService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import java.util.List;

@CrossOrigin
@RestController
@RequestMapping("/member")
public class MemberController {

    @Autowired
    private MemberService memberService;

    @PostMapping("/insert")
    public int insertMember(@RequestBody Member member){
        return memberService.insertMember(member);
    }
    @PostMapping("/update")
    public int updateMember(@RequestBody Member member){
        return memberService.updateMember(member);
    }
    @PostMapping("/delete")
    public int deleteMember(@RequestBody Member member){
        return memberService.deleteMember(member.getId());
    }
    @PostMapping("/find")
    public Member findMemberById(@RequestBody Member member){
        return memberService.findById(member.getId());
    }

    @GetMapping("/findall")
    public List<Member> findAll(){
        return memberService.findAll();
    }
}

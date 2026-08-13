package com.example.family_history_system.controller;
import com.example.family_history_system.common.response.Response;
import com.example.family_history_system.entity.Member;
import com.example.family_history_system.service.MemberService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@CrossOrigin
@RestController
@RequestMapping("/member")
public class MemberController {

    @Autowired
    private MemberService memberService;

    @PostMapping("/insert")
    public Response insertMember(@RequestBody Member member){
        boolean res = memberService.save(member);
        return res ? Response.buildSuccess("添加成员成功") : Response.buildFault("添加成员失败");
    }
    @PostMapping("/update")
    public Response updateMember(@RequestBody Member member){
        boolean res = memberService.updateById(member);
        return res ? Response.buildSuccess("更新成员成功") : Response.buildFault("更新成员失败");
    }
    @PostMapping("/delete")
    public Response deleteMember(@RequestBody Member member){
        boolean res = memberService.removeById(member.getId());
        return res ? Response.buildSuccess("删除成员成功") : Response.buildFault("删除成员失败");
    }
    @PostMapping("/find")
    public Response findMemberById(@RequestBody Member member){
        Member result = memberService.getById(member.getId());
        return result != null ? Response.buildSuccess("获取成员成功", result) : Response.buildFault("成员不存在");
    }

    @GetMapping("/findall")
    public Response findAll(){
        return Response.buildSuccess("获取所有成员成功", memberService.findAll());
    }
}


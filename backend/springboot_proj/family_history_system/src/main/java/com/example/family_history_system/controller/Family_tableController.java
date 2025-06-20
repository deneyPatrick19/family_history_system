package com.example.family_history_system.controller;

import com.example.family_history_system.entity.Family_table;
import com.example.family_history_system.mapper.Family_tableMapper;
import com.example.family_history_system.service.Family_tableService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/family_table")
public class Family_tableController {
    @Autowired
    Family_tableService family_tableService;

    @PostMapping("/insert")
    public int insertFamily_table(@RequestBody Family_table family_table){
        return family_tableService.insertFamily_table(family_table);
    }
    @PostMapping("/delete")
    public int deleteFamily_table(@RequestParam Integer id){
        return family_tableService.deleteFamily_table(id);
    }
    @PostMapping("/update")
    public int updateFamily_table(@RequestBody Family_table family_table){
        return family_tableService.updateFamily_table(family_table);
    }
    @PostMapping("/find")
    public Family_table findFamily_table(@RequestParam Integer id){
        return family_tableService.findFamily_table(id);
    }
    @GetMapping("/findall")
    public List<Family_table> findAllFamily_table(){
        return family_tableService.findAll();
    }
}

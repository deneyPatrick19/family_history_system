package com.example.family_history_system.controller;

import com.example.family_history_system.entity.Family_table;
import com.example.family_history_system.service.Family_tableService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;
import java.util.HashMap;

@RestController
@RequestMapping("/family-table")
@CrossOrigin
public class Family_tableController {

    @Autowired
    private Family_tableService familyTableService;

    @PostMapping("/insert")
    public int insert(@RequestBody Family_table familyTable){
        return familyTableService.insert(familyTable);
    }

    @PostMapping("/update")
    public int update(@RequestBody Family_table familyTable){
        return familyTableService.update(familyTable);
    }

    @PostMapping("/delete")
    public int delete(@RequestBody Family_table familyTable){
        return familyTableService.delete(familyTable.getId());
    }

    @PostMapping("/find")
    public Family_table find(@RequestBody Family_table familyTable){
        return familyTableService.findById(familyTable.getId());
    }

    @GetMapping("/findall")
    public List<Family_table> findAll(){
        return familyTableService.findAll();
    }

    /**
     * 获取用户的家族表列表
     */
    @GetMapping("/user/{userId}")
    public Map<String, Object> getUserFamilyTables(@PathVariable Integer userId) {
        Map<String, Object> result = new HashMap<>();
        
        try {
            List<Family_table> familyTables = familyTableService.findByUserId(userId);
            result.put("success", true);
            result.put("data", familyTables);
            result.put("message", "获取用户家族表成功");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "获取用户家族表失败: " + e.getMessage());
        }
        
        return result;
    }

    /**
     * 创建新的家族表
     */
    @PostMapping("/create")
    public Map<String, Object> createFamilyTable(@RequestBody Map<String, Object> tableData) {
        Map<String, Object> result = new HashMap<>();
        
        try {
            Family_table familyTable = new Family_table();
            familyTable.setUser_id(((Number) tableData.get("userId")).intValue());
            familyTable.setTable_name((String) tableData.get("tableName"));
            familyTable.setContent((String) tableData.get("content"));
            familyTable.setEstablish_time(new java.sql.Date(System.currentTimeMillis()));
            
            familyTableService.insert(familyTable);
            Integer tableId = familyTable.getId(); // 获取插入后的ID
            
            result.put("success", true);
            result.put("tableId", tableId);
            result.put("message", "创建家族表成功");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "创建家族表失败: " + e.getMessage());
        }
        
        return result;
    }

    /**
     * 编辑家族表
     */
    @PostMapping("/update-family-table")
    public Map<String, Object> updateFamilyTable(@RequestBody Map<String, Object> tableData) {
        Map<String, Object> result = new HashMap<>();
        try {
            Family_table familyTable = new Family_table();
            familyTable.setId(((Number) tableData.get("id")).intValue());
            familyTable.setTable_name((String) tableData.get("tableName"));
            familyTable.setContent((String) tableData.get("content"));
            int updateRes = familyTableService.update(familyTable);
            result.put("success", updateRes > 0);
            result.put("message", updateRes > 0 ? "编辑家族表成功" : "编辑家族表失败");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "编辑家族表失败: " + e.getMessage());
        }
        return result;
    }

    /**
     * 删除家族表
     */
    @PostMapping("/delete-family-table")
    public Map<String, Object> deleteFamilyTable(@RequestBody Map<String, Object> tableData) {
        Map<String, Object> result = new HashMap<>();
        try {
            Integer id = ((Number) tableData.get("id")).intValue();
            int delRes = familyTableService.delete(id);
            result.put("success", delRes > 0);
            result.put("message", delRes > 0 ? "删除家族表成功" : "删除家族表失败");
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "删除家族表失败: " + e.getMessage());
        }
        return result;
    }
} 
package com.example.family_history_system.controller;

import com.example.family_history_system.entity.Member;
import com.example.family_history_system.entity.Relationship;
import com.example.family_history_system.service.MemberService;
import com.example.family_history_system.service.RelationService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.text.SimpleDateFormat;
import java.util.*;

@RestController
@RequestMapping("/family-tree")
@CrossOrigin
public class FamilyTreeController {

    @Autowired
    private MemberService memberService;

    @Autowired
    private RelationService relationService;

    /**
     * 获取指定家族表的家谱树数据
     */
    @GetMapping("/{familyTableId}")
    public Map<String, Object> getFamilyTree(@PathVariable Integer familyTableId) {
        Map<String, Object> result = new HashMap<>();
        
        try {
            // 获取该家族表下的所有成员
            List<Member> members = memberService.findByFamilyTableId(familyTableId);
            
            // 获取所有关系
            List<Relationship> relationships = relationService.findAllRelation();
            
            // 构建家谱树
            List<Map<String, Object>> treeData = buildFamilyTree(members, relationships);
            
            result.put("success", true);
            result.put("data", treeData);
            result.put("message", "获取家谱树成功");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "获取家谱树失败: " + e.getMessage());
        }
        
        return result;
    }

    /**
     * 保存家谱树节点
     */
    @PostMapping("/save-node")
    public Map<String, Object> saveNode(@RequestBody Map<String, Object> nodeData) {
        Map<String, Object> result = new HashMap<>();
        
        try {
            Member member = new Member();
            member.setFamily_table_id(((Number) nodeData.get("familyTableId")).intValue());
            member.setName((String) nodeData.get("name"));
            member.setGender((String) nodeData.get("gender"));
            
            // 处理日期
            if (nodeData.get("birthDate") != null && !((String) nodeData.get("birthDate")).isEmpty()) {
                SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
                Date birthDate = sdf.parse((String) nodeData.get("birthDate"));
                member.setBirthdate(new java.sql.Date(birthDate.getTime()));
            }
            
            memberService.insertMember(member);
            Integer memberId = member.getId(); // 获取插入后的ID
            
            // 如果有父节点关系，保存关系
            if (nodeData.get("parentId") != null) {
                Relationship relation = new Relationship();
                relation.setMember_id1(((Number) nodeData.get("parentId")).intValue());
                relation.setMember_id2(memberId);
                relation.setRelation((String) nodeData.get("relationship"));
                relationService.insertRelation(relation);
            }
            
            // 如果有兄弟姐妹关系，保存关系
            if (nodeData.get("siblingId") != null) {
                saveSiblingRelation(memberId, ((Number) nodeData.get("siblingId")).intValue(), 
                                  (String) nodeData.get("relationship"));
            }
            
            result.put("success", true);
            result.put("memberId", memberId);
            result.put("message", "保存节点成功");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "保存节点失败: " + e.getMessage());
        }
        
        return result;
    }

    /**
     * 保存兄弟姐妹关系
     */
    private void saveSiblingRelation(Integer memberId1, Integer memberId2, String relationship) {
        // 根据性别确定具体的关系类型
        Member member1 = memberService.findById(memberId1);
        Member member2 = memberService.findById(memberId2);
        
        if (member1 != null && member2 != null) {
            String relationType = determineSiblingRelation(member1.getGender(), member2.getGender(), relationship);
            
            // 保存双向关系
            Relationship relation1 = new Relationship();
            relation1.setMember_id1(memberId1);
            relation1.setMember_id2(memberId2);
            relation1.setRelation(relationType);
            relationService.insertRelation(relation1);
            
            Relationship relation2 = new Relationship();
            relation2.setMember_id1(memberId2);
            relation2.setMember_id2(memberId1);
            relation2.setRelation(getReverseRelation(relationType));
            relationService.insertRelation(relation2);
        }
    }

    /**
     * 确定兄弟姐妹关系类型
     */
    private String determineSiblingRelation(String gender1, String gender2, String relationship) {
        if (gender1.equals("男") && gender2.equals("男")) {
            return "兄弟";
        } else if (gender1.equals("女") && gender2.equals("女")) {
            return "姐妹";
        } else if (gender1.equals("男") && gender2.equals("女")) {
            return "兄妹";
        } else if (gender1.equals("女") && gender2.equals("男")) {
            return "姐弟";
        } else {
            return relationship; // 使用传入的关系类型
        }
    }

    /**
     * 获取反向关系
     */
    private String getReverseRelation(String relation) {
        switch (relation) {
            case "兄弟": return "兄弟";
            case "姐妹": return "姐妹";
            case "兄妹": return "兄妹";
            case "姐弟": return "姐弟";
            default: return relation;
        }
    }

    /**
     * 更新家谱树节点
     */
    @PostMapping("/update-node")
    public Map<String, Object> updateNode(@RequestBody Map<String, Object> nodeData) {
        Map<String, Object> result = new HashMap<>();
        
        try {
            Member member = new Member();
            member.setId(((Number) nodeData.get("id")).intValue());
            member.setName((String) nodeData.get("name"));
            member.setGender((String) nodeData.get("gender"));
            
            // 处理日期
            if (nodeData.get("birthDate") != null && !((String) nodeData.get("birthDate")).isEmpty()) {
                SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
                Date birthDate = sdf.parse((String) nodeData.get("birthDate"));
                member.setBirthdate(new java.sql.Date(birthDate.getTime()));
            }
            
            memberService.updateMember(member);
            
            result.put("success", true);
            result.put("message", "更新节点成功");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "更新节点失败: " + e.getMessage());
        }
        
        return result;
    }

    /**
     * 删除家谱树节点
     */
    @PostMapping("/delete-node")
    public Map<String, Object> deleteNode(@RequestBody Map<String, Object> nodeData) {
        Map<String, Object> result = new HashMap<>();
        
        try {
            Integer memberId = ((Number) nodeData.get("id")).intValue();
            
            // 删除相关的关系
            relationService.deleteRelationsByMemberId(memberId);
            
            // 删除成员
            memberService.deleteMember(memberId);
            
            result.put("success", true);
            result.put("message", "删除节点成功");
            
        } catch (Exception e) {
            result.put("success", false);
            result.put("message", "删除节点失败: " + e.getMessage());
        }
        
        return result;
    }

    /**
     * 构建家谱树结构
     */
    private List<Map<String, Object>> buildFamilyTree(List<Member> members, List<Relationship> relationships) {
        Map<Integer, Map<String, Object>> memberMap = new HashMap<>();
        Map<Integer, List<Integer>> childrenMap = new HashMap<>();
        Map<Integer, List<Integer>> siblingsMap = new HashMap<>();
        Map<Integer, Integer> parentMap = new HashMap<>();
        
        // 初始化成员映射
        for (Member member : members) {
            Map<String, Object> node = new HashMap<>();
            node.put("id", member.getId());
            node.put("name", member.getName());
            node.put("gender", member.getGender());
            node.put("birthDate", member.getBirthdate());
            node.put("deathDate", member.getDeathdate());
            node.put("icon", member.getIcon());
            node.put("children", new ArrayList<>());
            node.put("siblings", new ArrayList<>());
            
            memberMap.put(member.getId(), node);
            childrenMap.put(member.getId(), new ArrayList<>());
            siblingsMap.put(member.getId(), new ArrayList<>());
        }
        
        // 构建父子关系和兄弟姐妹关系
        for (Relationship relation : relationships) {
            String relationType = relation.getRelation();
            
            if (relationType.contains("父") || relationType.contains("子")) {
                // 父子关系
                List<Integer> children = childrenMap.get(relation.getMember_id1());
                if (children != null) {
                    children.add(relation.getMember_id2());
                }
                parentMap.put(relation.getMember_id2(), relation.getMember_id1());
            } else if (relationType.contains("兄") || relationType.contains("弟") || 
                      relationType.contains("姐") || relationType.contains("妹") ||
                      relationType.contains("兄弟") || relationType.contains("姐妹")) {
                // 兄弟姐妹关系
                List<Integer> siblings1 = siblingsMap.get(relation.getMember_id1());
                if (siblings1 != null) {
                    siblings1.add(relation.getMember_id2());
                }
                
                List<Integer> siblings2 = siblingsMap.get(relation.getMember_id2());
                if (siblings2 != null) {
                    siblings2.add(relation.getMember_id1());
                }
            }
        }
        
        // 将兄弟姐妹信息添加到节点数据中
        for (Map.Entry<Integer, List<Integer>> entry : siblingsMap.entrySet()) {
            Integer memberId = entry.getKey();
            List<Integer> siblingIds = entry.getValue();
            
            Map<String, Object> node = memberMap.get(memberId);
            if (node != null && !siblingIds.isEmpty()) {
                List<Map<String, Object>> siblings = new ArrayList<>();
                for (Integer siblingId : siblingIds) {
                    Map<String, Object> siblingNode = memberMap.get(siblingId);
                    if (siblingNode != null) {
                        // 只取基本字段，避免递归
                        Map<String, Object> simpleSibling = new HashMap<>();
                        simpleSibling.put("id", siblingNode.get("id"));
                        simpleSibling.put("name", siblingNode.get("name"));
                        simpleSibling.put("gender", siblingNode.get("gender"));
                        simpleSibling.put("birthDate", siblingNode.get("birthDate"));
                        simpleSibling.put("deathDate", siblingNode.get("deathDate"));
                        simpleSibling.put("icon", siblingNode.get("icon"));
                        siblings.add(simpleSibling);
                    }
                }
                node.put("siblings", siblings);
            }
        }
        
        // 构建树结构
        List<Map<String, Object>> rootNodes = new ArrayList<>();
        Set<Integer> hasParent = new HashSet<>();
        
        for (Relationship relation : relationships) {
            if (relation.getRelation().contains("父") || relation.getRelation().contains("子")) {
                hasParent.add(relation.getMember_id2());
            }
        }
        
        for (Member member : members) {
            if (!hasParent.contains(member.getId())) {
                // 这是一个根节点
                Map<String, Object> rootNode = memberMap.get(member.getId());
                buildChildrenWithSiblings(rootNode, childrenMap, siblingsMap, parentMap, memberMap);
                rootNodes.add(rootNode);
            }
        }
        
        return rootNodes;
    }

    /**
     * 递归构建子节点，包含兄弟姐妹关系
     */
    private void buildChildrenWithSiblings(Map<String, Object> parentNode, Map<Integer, List<Integer>> childrenMap, 
                                         Map<Integer, List<Integer>> siblingsMap, Map<Integer, Integer> parentMap,
                                         Map<Integer, Map<String, Object>> memberMap) {
        Integer parentId = (Integer) parentNode.get("id");
        List<Integer> childrenIds = childrenMap.get(parentId);
        
        if (childrenIds != null && !childrenIds.isEmpty()) {
            List<Map<String, Object>> children = new ArrayList<>();
            
            // 按出生日期排序（如果有的话）
            childrenIds.sort((id1, id2) -> {
                Map<String, Object> node1 = memberMap.get(id1);
                Map<String, Object> node2 = memberMap.get(id2);
                Date date1 = (Date) node1.get("birthDate");
                Date date2 = (Date) node2.get("birthDate");
                
                if (date1 == null && date2 == null) return 0;
                if (date1 == null) return 1;
                if (date2 == null) return -1;
                
                return date1.compareTo(date2);
            });
            
            for (Integer childId : childrenIds) {
                Map<String, Object> childNode = memberMap.get(childId);
                if (childNode != null) {
                    // 递归构建子节点
                    buildChildrenWithSiblings(childNode, childrenMap, siblingsMap, parentMap, memberMap);
                    children.add(childNode);
                }
            }
            parentNode.put("children", children);
        }

        // siblings只展示基本信息，不递归嵌套
        List<Integer> siblingIds = siblingsMap.get(parentId);
        if (siblingIds != null && !siblingIds.isEmpty()) {
            List<Map<String, Object>> siblings = new ArrayList<>();
            for (Integer siblingId : siblingIds) {
                Map<String, Object> siblingNode = memberMap.get(siblingId);
                if (siblingNode != null) {
                    // 只取基本字段，避免递归
                    Map<String, Object> simpleSibling = new HashMap<>();
                    simpleSibling.put("id", siblingNode.get("id"));
                    simpleSibling.put("name", siblingNode.get("name"));
                    simpleSibling.put("gender", siblingNode.get("gender"));
                    simpleSibling.put("birthDate", siblingNode.get("birthDate"));
                    simpleSibling.put("deathDate", siblingNode.get("deathDate"));
                    simpleSibling.put("icon", siblingNode.get("icon"));
                    siblings.add(simpleSibling);
                }
            }
            parentNode.put("siblings", siblings);
        }
    }
} 
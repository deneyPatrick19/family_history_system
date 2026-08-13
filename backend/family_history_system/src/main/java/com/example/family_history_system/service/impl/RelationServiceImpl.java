package com.example.family_history_system.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.example.family_history_system.entity.Relationship;
import com.example.family_history_system.mapper.RelationMapper;
import com.example.family_history_system.service.RelationService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class RelationServiceImpl extends ServiceImpl<RelationMapper, Relationship> implements RelationService {

    /**
     * 新增成员关系
     * @param relation 关系实体（含 member_id1、member_id2、relation）
     * @return true 新增成功
     */
    @Override
    public Boolean insertRelation(Relationship relation){
        return this.save(relation);
    }

    /**
     * 查询全部成员关系
     * @return 关系列表
     */
    @Override
    public List<Relationship> findAllRelation(){
        return this.list(new LambdaQueryWrapper<>());
    }

    /**
     * 按双向主键查询关系
     * @param id1 成员1 ID
     * @param id2 成员2 ID
     * @return 关系实体；不存在返回 null
     */
    @Override
    public Relationship findRelationById(Integer id1, Integer id2){
        return this.getOne(new LambdaQueryWrapper<Relationship>()
                .eq(Relationship::getMember_id1, id1)
                .eq(Relationship::getMember_id2, id2));
    }

    /**
     * 按双向主键删除关系
     * @param id1 成员1 ID
     * @param id2 成员2 ID
     * @return true 删除成功
     */
    @Override
    public Boolean deleteRelationById(Integer id1, Integer id2){
        return this.remove(new LambdaQueryWrapper<Relationship>()
                .eq(Relationship::getMember_id1, id1)
                .eq(Relationship::getMember_id2, id2));
    }

    /**
     * 按双向主键更新关系类型
     * @param relation 含主键与新关系描述的关系实体
     * @return true 更新成功
     */
    @Override
    public Boolean updateRelationById(Relationship relation){
        return this.update(relation, new LambdaQueryWrapper<Relationship>()
                .eq(Relationship::getMember_id1, relation.getMember_id1())
                .eq(Relationship::getMember_id2, relation.getMember_id2()));
    }

    /**
     * 删除涉及指定成员的全部关系（双向：作为 id1 或 id2）
     * @param memberId 成员ID
     * @return 受影响行数
     */
    @Override
    public int deleteRelationsByMemberId(Integer memberId){
        return this.baseMapper.delete(new LambdaQueryWrapper<Relationship>()
                .eq(Relationship::getMember_id1, memberId)
                .or()
                .eq(Relationship::getMember_id2, memberId));
    }

    /**
     * 查询以指定成员为 id2 的全部关系
     * @param memberId2 成员2 ID
     * @return 关系列表
     */
    @Override
    public List<Relationship> findByMemberId2(Integer memberId2){
        return this.list(new LambdaQueryWrapper<Relationship>()
                .eq(Relationship::getMember_id2, memberId2));
    }
}

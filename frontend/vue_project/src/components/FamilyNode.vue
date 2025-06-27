<template>
  <div class="tree-node">
    <div class="node-content" :class="{ 'selected': selectedNode === node }" @click="selectNode(node)">
      <div class="node-avatar">
        <el-avatar :size="30" :src="node.avatar">{{ node.name.charAt(0) }}</el-avatar>
      </div>
      <div class="node-info">
        <div class="node-name">{{ node.name }}</div>
        <div class="node-details">{{ formatDate(node.birthDate) }} | {{ node.gender }}</div>
        <div v-if="node.deathDate" class="node-death">死亡: {{ formatDate(node.deathDate) }}</div>
        <div v-if="node.parentName" class="node-parent">父节点: {{ node.parentName }}</div>
        <div v-if="node.bio" class="node-bio">{{ node.bio }}</div>
      </div>
      <div class="node-actions">
        <el-button size="small" type="primary" @click.stop="addChild(node)">添加子节点</el-button>
        <el-button 
          size="small" 
          type="info" 
          @click.stop="async () => await addParent(node)"
          :disabled="node.parentId"
          :title="node.parentId ? '该节点已有父节点' : '添加父节点'"
        >添加父节点</el-button>
        <el-button size="small" type="warning" @click.stop="viewNode(node)">查看</el-button>
        <el-button size="small" type="danger" @click.stop="deleteNode(node)">删除</el-button>
      </div>
    </div>
    <div class="children-container" v-if="node.children && node.children.length > 0">
      <div class="children-wrapper">
        <FamilyNode
          v-for="child in node.children"
          :key="child.id"
          :node="child"
          :selectedNode="selectedNode"
          :selectNode="selectNode"
          :addChild="addChild"
          :addParent="addParent"
          :viewNode="viewNode"
          :deleteNode="deleteNode"
          :formatDate="formatDate"
        />
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'FamilyNode',
  props: [
    'node', 'selectedNode', 'selectNode',
    'addChild', 'addParent', 'viewNode', 'deleteNode', 'formatDate'
  ]
}
</script>

<style scoped>
.tree-node {
  display: flex;
  flex-direction: column;
  align-items: center;
}
.node-content {
  display: flex;
  align-items: center;
  background: white;
  border: 2px solid #e4e7ed;
  border-radius: 8px;
  padding: 15px;
  margin: 10px;
  min-width: 300px;
  cursor: pointer;
  transition: all 0.3s ease;
  box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}
.node-content.selected {
  border-color: #409eff;
  background: #f0f9ff;
}
.node-avatar {
  margin-right: 15px;
}
.node-info {
  flex: 1;
  min-width: 0;
}
.node-name {
  font-weight: bold;
  font-size: 16px;
  color: #303133;
  margin-bottom: 5px;
}
.node-details {
  font-size: 12px;
  color: #909399;
}
.node-death {
  font-size: 11px;
  color: #f56c6c;
  margin-top: 2px;
}
.node-parent {
  font-size: 11px;
  color: #67c23a;
  margin-top: 2px;
}
.node-bio {
  font-size: 12px;
  color: #909399;
  margin-top: 5px;
}
.node-actions {
  display: flex;
  gap: 5px;
  margin-left: 15px;
}
.children-container {
  position: relative;
  margin-top: 20px;
}
.children-wrapper {
  display: flex;
  gap: 40px;
  position: relative;
}
</style> 
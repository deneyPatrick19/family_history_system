<template>
  <div class="tree-node">
    <div class="node-content" :class="{ 'selected': selectedNode === node }" @click="selectNode(node)">
      <div class="node-avatar">
        <el-avatar :size="30" :src="node.avatar">{{ node.name.charAt(0) }}</el-avatar>
      </div>
      <div class="node-info">
        <div class="node-name">{{ node.name }}</div>
        <div class="node-details">{{ formatDate(node.birthDate) }} | {{ node.gender }}</div>
      </div>
      <div class="node-actions">
        <el-button size="small" type="primary" @click.stop="addChild(node)">添加子节点</el-button>
        <el-button size="small" type="info" @click.stop="addParent(node)">添加父节点</el-button>
        <el-button size="small" type="warning" @click.stop="editNode(node)">编辑</el-button>
        <el-button size="small" type="success" @click.stop="addSibling(node)">添加平辈节点</el-button>
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
          :editNode="editNode"
          :addSibling="addSibling"
          :deleteNode="deleteNode"
          :formatDate="formatDate"
        />
      </div>
    </div>
    <div class="siblings-container" v-if="node.siblings && node.siblings.length > 0">
      <div class="siblings-label">兄弟姐妹：</div>
      <div class="siblings-wrapper">
        <FamilyNode
          v-for="sibling in node.siblings"
          :key="sibling.id"
          :node="sibling"
          :selectedNode="selectedNode"
          :selectNode="selectNode"
          :addChild="addChild"
          :addParent="addParent"
          :editNode="editNode"
          :addSibling="addSibling"
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
    'addChild', 'addParent', 'editNode', 'addSibling', 'deleteNode', 'formatDate'
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
.siblings-container {
  position: relative;
  margin-top: 15px;
  padding: 10px;
  background: #f8f9fa;
  border-radius: 8px;
  border: 1px solid #e9ecef;
}
.siblings-label {
  font-size: 12px;
  color: #6c757d;
  margin-bottom: 10px;
  text-align: center;
  font-weight: 500;
}
.siblings-wrapper {
  display: flex;
  gap: 20px;
  position: relative;
}
</style> 
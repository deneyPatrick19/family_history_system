<template>
  <div class="family-tree">
    <div class="tree-header">
      <h2>家族树管理</h2>
      <div class="header-actions">
        <el-button type="primary" @click="addRootNode">添加根节点</el-button>
        <el-button type="success" @click="expandAll">展开全部</el-button>
        <el-button type="warning" @click="collapseAll">收起全部</el-button>
      </div>
    </div>

    <div class="tree-container">
      <div class="tree-wrapper">
        <FamilyNode
          v-if="rootNode"
          :node="rootNode"
          :selectedNode="selectedNode"
          :selectNode="selectNode"
          :addChild="addChild"
          :addParent="addParent"
          :editNode="editNode"
          :addSibling="addSibling"
          :deleteNode="deleteNode"
          :formatDate="formatDate"
        />
        <div v-else class="empty-tree">
          <el-empty description="暂无家族树数据，请添加根节点开始创建">
            <el-button type="primary" @click="addRootNode">添加根节点</el-button>
          </el-empty>
        </div>
      </div>
    </div>

    <!-- 节点编辑对话框 -->
    <el-dialog v-model="dialogVisible" :title="dialogTitle" width="500px">
      <el-form :model="editingNode" :rules="nodeRules" ref="nodeForm" label-width="80px">
        <el-form-item label="姓名" prop="name">
          <el-input v-model="editingNode.name" placeholder="请输入姓名" />
        </el-form-item>
        <el-form-item label="出生日期" prop="birthDate">
          <el-date-picker v-model="editingNode.birthDate" type="date" placeholder="选择出生日期" style="width: 100%;" />
        </el-form-item>
        <el-form-item label="性别" prop="gender">
          <el-select v-model="editingNode.gender" placeholder="请选择性别" style="width: 100%;">
            <el-option label="男" value="男" />
            <el-option label="女" value="女" />
          </el-select>
        </el-form-item>
        <el-form-item label="关系" prop="relationship">
          <el-input v-model="editingNode.relationship" placeholder="请输入与父节点的关系" />
        </el-form-item>
        <el-form-item label="简介">
          <el-input v-model="editingNode.bio" type="textarea" :rows="3" placeholder="请输入个人简介" />
        </el-form-item>
      </el-form>
      <template #footer>
        <span class="dialog-footer">
          <el-button @click="dialogVisible = false">取消</el-button>
          <el-button type="primary" @click="saveNode">确定</el-button>
        </span>
      </template>
    </el-dialog>
  </div>
</template>

<script>
import FamilyNode from '../components/FamilyNode.vue';
export default {
  name: 'FamilyTree',
  components: { FamilyNode },
  data() {
    return {
      rootNode: null,
      selectedNode: null,
      dialogVisible: false,
      dialogTitle: '添加节点',
      editingNode: {
        name: '',
        birthDate: '',
        gender: '男',
        relationship: '',
        bio: ''
      },
      nodeRules: {
        name: [
          { required: true, message: '请输入姓名', trigger: 'blur' }
        ],
        birthDate: [
          { required: true, message: '请选择出生日期', trigger: 'change' }
        ],
        gender: [
          { required: true, message: '请选择性别', trigger: 'change' }
        ]
      },
      nextId: 1
    }
  },
  mounted() {
    this.loadTreeData();
    this.$nextTick(() => {
      const container = this.$el.querySelector('.tree-container');
      if (container) {
        container.scrollLeft = 0;
      }
    });
  },
  methods: {
    // 加载树形数据
    loadTreeData() {
      const username = this.$store.getters.user.username;
      if (username) {
        const saved = localStorage.getItem(`familyTree_${username}`);
        if (saved) {
          const data = JSON.parse(saved);
          this.rootNode = data.rootNode;
          this.nextId = data.nextId || 1;
        }
      }
    },

    // 保存树形数据
    saveTreeData() {
      const username = this.$store.getters.user.username;
      if (username) {
        localStorage.setItem(`familyTree_${username}`, JSON.stringify({
          rootNode: this.rootNode,
          nextId: this.nextId
        }));
      }
    },

    // 生成唯一ID
    generateId() {
      return this.nextId++;
    },

    // 添加根节点
    addRootNode() {
      this.dialogTitle = '添加根节点';
      this.editingNode = {
        name: '',
        birthDate: '',
        gender: '男',
        relationship: '根节点',
        bio: ''
      };
      this.dialogVisible = true;
    },

    // 添加子节点
    addChild(parentNode) {
      this.dialogTitle = '添加子节点';
      this.editingNode = {
        name: '',
        birthDate: '',
        gender: '男',
        relationship: '',
        bio: '',
        parentId: parentNode.id
      };
      this.dialogVisible = true;
    },

    // 添加父节点
    addParent(node) {
      this.dialogTitle = '添加父节点';
      this.editingNode = {
        name: '',
        birthDate: '',
        gender: '男',
        relationship: '',
        bio: '',
        childId: node.id
      };
      this.dialogVisible = true;
    },

    // 编辑节点
    editNode(node) {
      this.dialogTitle = '编辑节点';
      this.editingNode = { ...node };
      this.dialogVisible = true;
    },

    // 删除节点
    deleteNode(node) {
      this.$confirm('确定要删除这个节点吗？删除后其所有子节点也会被删除。', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        if (node === this.rootNode) {
          this.rootNode = null;
        } else {
          this.removeNodeFromParent(node);
        }
        this.saveTreeData();
        this.$message.success('删除成功');
      }).catch(() => {
        // 取消删除
      });
    },

    // 从父节点中删除子节点
    removeNodeFromParent(node) {
      const findAndRemove = (parent) => {
        if (parent.children) {
          const index = parent.children.findIndex(child => child.id === node.id);
          if (index !== -1) {
            parent.children.splice(index, 1);
            return true;
          }
          for (let child of parent.children) {
            if (findAndRemove(child)) {
              return true;
            }
          }
        }
        return false;
      };
      findAndRemove(this.rootNode);
    },

    // 保存节点
    saveNode() {
      this.$refs.nodeForm.validate((valid) => {
        if (valid) {
          // 格式化日期，只保留年月日
          if (this.editingNode.birthDate && typeof this.editingNode.birthDate === 'string') {
            this.editingNode.birthDate = this.editingNode.birthDate.slice(0, 10);
          }
          if (this.editingNode.childId) {
            this.createParentNode(this.editingNode);
          } else if (this.editingNode.siblingOf) {
            this.createSiblingNode(this.editingNode);
          } else if (this.editingNode.id) {
            this.updateNode(this.editingNode);
          } else {
            this.createNode(this.editingNode);
          }
          this.dialogVisible = false;
          this.saveTreeData();
          this.$message.success('保存成功');
        }
      });
    },

    // 创建新节点
    createNode(nodeData) {
      const newNode = {
        id: this.generateId(),
        name: nodeData.name,
        birthDate: nodeData.birthDate,
        gender: nodeData.gender,
        relationship: nodeData.relationship,
        bio: nodeData.bio,
        children: []
      };

      if (nodeData.parentId) {
        // 添加子节点
        this.addNodeToParent(newNode, nodeData.parentId);
      } else {
        // 添加根节点
        this.rootNode = newNode;
      }
    },

    // 更新节点
    updateNode(nodeData) {
      const updateNodeData = (node) => {
        if (node.id === nodeData.id) {
          Object.assign(node, nodeData);
          return true;
        }
        if (node.children) {
          for (let child of node.children) {
            if (updateNodeData(child)) {
              return true;
            }
          }
        }
        return false;
      };
      updateNodeData(this.rootNode);
    },

    // 将节点添加到父节点
    addNodeToParent(newNode, parentId) {
      const addToParent = (node) => {
        if (node.id === parentId) {
          if (!node.children) {
            node.children = [];
          }
          node.children.push(newNode);
          return true;
        }
        if (node.children) {
          for (let child of node.children) {
            if (addToParent(child)) {
              return true;
            }
          }
        }
        return false;
      };
      addToParent(this.rootNode);
    },

    // 创建父节点
    createParentNode(nodeData) {
      const newNode = {
        id: this.generateId(),
        name: nodeData.name,
        birthDate: nodeData.birthDate,
        gender: nodeData.gender,
        relationship: nodeData.relationship,
        bio: nodeData.bio,
        children: []
      };

      // 找到childId对应的节点
      const findAndReplace = (parent, childId) => {
        if (parent.id === childId) {
          // 新父节点替换原节点
          newNode.children = [JSON.parse(JSON.stringify(parent))];
          // 如果是根节点
          if (this.rootNode.id === childId) {
            this.rootNode = newNode;
          } else {
            this.replaceNodeInTree(this.rootNode, childId, newNode);
          }
          return true;
        }
        if (parent.children) {
          for (let child of parent.children) {
            if (findAndReplace(child, childId)) {
              return true;
            }
          }
        }
        return false;
      };

      findAndReplace(this.rootNode, nodeData.childId);
    },

    // 替换节点
    replaceNodeInTree(parent, childId, newNode) {
      if (!parent.children) return false;
      const idx = parent.children.findIndex(child => child.id === childId);
      if (idx !== -1) {
        parent.children[idx] = newNode;
        return true;
      }
      for (let child of parent.children) {
        if (this.replaceNodeInTree(child, childId, newNode)) {
          return true;
        }
      }
      return false;
    },

    // 选择节点
    selectNode(node) {
      this.selectedNode = node;
    },

    // 展开全部
    expandAll() {
      // 这里可以添加展开逻辑，目前默认都是展开的
      this.$message.info('所有节点已展开');
    },

    // 收起全部
    collapseAll() {
      // 这里可以添加收起逻辑
      this.$message.info('所有节点已收起');
    },

    // 新增 addSibling 方法
    addSibling(node) {
      this.dialogTitle = '添加平辈节点';
      this.editingNode = {
        name: '',
        birthDate: '',
        gender: '男',
        relationship: '',
        bio: '',
        siblingOf: node.id // 记录要添加平辈节点的目标节点id
      };
      this.dialogVisible = true;
    },

    // 新增 createSiblingNode 方法
    createSiblingNode(nodeData) {
      const newNode = {
        id: this.generateId(),
        name: nodeData.name,
        birthDate: nodeData.birthDate,
        gender: nodeData.gender,
        relationship: nodeData.relationship,
        bio: nodeData.bio,
        children: []
      };

      // 根节点不能添加平辈节点
      if (this.rootNode.id === nodeData.siblingOf) {
        this.$message.warning('根节点不能添加平辈节点');
        return;
      }

      // 在树中找到 siblingOf 的父节点，并插入新节点
      const addSibling = (parent) => {
        if (parent.children) {
          const idx = parent.children.findIndex(child => child.id === nodeData.siblingOf);
          if (idx !== -1) {
            parent.children.splice(idx + 1, 0, newNode);
            return true;
          }
          for (let child of parent.children) {
            if (addSibling(child)) return true;
          }
        }
        return false;
      };
      addSibling(this.rootNode);
    },

    formatDate(dateStr) {
      if (!dateStr) return '';
      // 只取前10位，防止有时带时分秒
      return dateStr.length > 10 ? dateStr.slice(0, 10) : dateStr;
    }
  }
}
</script>

<style scoped>
.family-tree {
  padding: 20px;
  height: 100vh;
  overflow: auto;
}

.tree-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
  padding-bottom: 15px;
  border-bottom: 1px solid #e4e7ed;
}

.tree-header h2 {
  margin: 0;
  color: #303133;
}

.header-actions {
  display: flex;
  gap: 10px;
}

.tree-container {
  min-height: 500px;
  background: #fafafa;
  border-radius: 8px;
  padding: 20px;
  overflow-x: auto;
  overflow-y: auto;
}

.tree-wrapper {
  display: flex;
  justify-content: center;
  min-width: fit-content;
  min-height: fit-content;
  max-height: 100%;
  overflow-y: auto;
}

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

.node-content:hover {
  border-color: #409eff;
  box-shadow: 0 4px 8px rgba(0,0,0,0.15);
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

.children-container::before {
  content: '';
  position: absolute;
  top: -10px;
  left: 50%;
  width: 2px;
  height: 10px;
  background: #e4e7ed;
}

.children-wrapper {
  display: flex;
  gap: 40px;
  position: relative;
}

.children-wrapper::before {
  content: '';
  position: absolute;
  top: -10px;
  left: 0;
  right: 0;
  height: 2px;
  background: #e4e7ed;
}

.child-node {
  position: relative;
}

.child-node::before {
  content: '';
  position: absolute;
  top: -10px;
  left: 50%;
  width: 2px;
  height: 10px;
  background: #e4e7ed;
}

.grandchild-node .node-content {
  min-width: 250px;
  padding: 10px;
}

.empty-tree {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 400px;
}

.dialog-footer {
  display: flex;
  justify-content: flex-end;
  gap: 10px;
}
</style>
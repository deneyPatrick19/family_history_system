<template>
  <div class="family-tree">
    <!-- 家族表选择器 -->
    <div v-if="!selectedFamilyTableId" class="table-selector-container">
      <FamilyTableSelector 
        :userId="userId" 
        @table-selected="onTableSelected" 
      />
    </div>

    <!-- 家谱树管理界面 -->
    <div v-else class="tree-management">
      <div class="tree-header">
        <div class="header-left">
          <h2>家族树管理</h2>
          <el-button type="text" @click="backToSelector">切换家族表</el-button>
        </div>
        <div class="header-actions">
          <el-button type="primary" @click="addRootNode">添加根节点</el-button>
          <el-button type="success" @click="expandAll">展开全部</el-button>
          <el-button type="warning" @click="collapseAll">收起全部</el-button>
          <el-button type="info" @click="refreshTree">刷新数据</el-button>
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
    </div>

    <!-- 节点编辑对话框 -->
    <el-dialog v-model="dialogVisible" :title="dialogTitle" width="500px">
      <el-form :model="editingNode" :rules="nodeRules" ref="nodeForm" label-width="80px">
        <el-form-item label="姓名" prop="name">
          <el-input v-model="editingNode.name" placeholder="请输入姓名" />
        </el-form-item>
        <el-form-item label="出生日期" prop="birthDate">
          <el-date-picker 
            v-model="editingNode.birthDate" 
            type="date" 
            placeholder="选择出生日期" 
            format="YYYY-MM-DD"
            value-format="YYYY-MM-DD"
            style="width: 100%;" 
          />
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
import FamilyTableSelector from '../components/FamilyTableSelector.vue';
import { familyTreeAPI } from '../api/familyTree';

export default {
  name: 'FamilyTree',
  components: { FamilyNode, FamilyTableSelector },
  data() {
    return {
      selectedFamilyTableId: null,
      userId: 1, // 默认用户ID，实际应该从用户信息中获取
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
      loading: false
    }
  },
  mounted() {
    // 从store获取用户信息
    const user = this.$store.getters.user;
    if (user && user.id) {
      this.userId = user.id;
    }
  },
  methods: {
    // 家族表选择回调
    onTableSelected(tableId) {
      this.selectedFamilyTableId = tableId;
      this.loadTreeData();
    },

    // 返回家族表选择器
    backToSelector() {
      this.selectedFamilyTableId = null;
      this.rootNode = null;
    },

    // 从后端加载树形数据
    async loadTreeData() {
      if (!this.selectedFamilyTableId) return;
      
      this.loading = true;
      try {
        const response = await familyTreeAPI.getFamilyTree(this.selectedFamilyTableId);
        if (response.data.success) {
          const treeData = response.data.data;
          if (treeData && treeData.length > 0) {
            this.rootNode = treeData[0]; // 假设只有一个根节点
          } else {
            this.rootNode = null;
          }
        } else {
          this.$message.error(response.data.message || '加载家谱树失败');
        }
      } catch (error) {
        console.error('加载家谱树失败:', error);
        this.$message.error('加载家谱树失败，请检查网络连接');
      } finally {
        this.loading = false;
      }
    },

    // 刷新数据
    refreshTree() {
      this.loadTreeData();
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
      }).then(async () => {
        try {
          const response = await familyTreeAPI.deleteNode({
            id: node.id
          });
          
          if (response.data.success) {
            this.$message.success('删除成功');
            this.loadTreeData(); // 重新加载数据
          } else {
            this.$message.error(response.data.message || '删除失败');
          }
        } catch (error) {
          console.error('删除节点失败:', error);
          this.$message.error('删除节点失败，请检查网络连接');
        }
      }).catch(() => {
        // 取消删除
      });
    },

    // 保存节点
    async saveNode() {
      this.$refs.nodeForm.validate(async (valid) => {
        if (valid) {
          try {
            let response;
            const nodeData = {
              familyTableId: this.selectedFamilyTableId,
              name: this.editingNode.name,
              gender: this.editingNode.gender,
              birthDate: this.editingNode.birthDate,
              relationship: this.editingNode.relationship
            };

            if (this.editingNode.id) {
              // 更新节点
              nodeData.id = this.editingNode.id;
              response = await familyTreeAPI.updateNode(nodeData);
            } else {
              // 新增节点
              if (this.editingNode.parentId) {
                nodeData.parentId = this.editingNode.parentId;
              }
              if (this.editingNode.siblingOf) {
                nodeData.siblingId = this.editingNode.siblingOf;
              }
              response = await familyTreeAPI.saveNode(nodeData);
            }

            if (response.data.success) {
              this.$message.success('保存成功');
              this.dialogVisible = false;
              this.loadTreeData(); // 重新加载数据
            } else {
              this.$message.error(response.data.message || '保存失败');
            }
          } catch (error) {
            console.error('保存节点失败:', error);
            this.$message.error('保存节点失败，请检查网络连接');
          }
        }
      });
    },

    // 选择节点
    selectNode(node) {
      this.selectedNode = node;
    },

    // 展开全部
    expandAll() {
      this.$message.info('所有节点已展开');
    },

    // 收起全部
    collapseAll() {
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
        siblingOf: node.id
      };
      this.dialogVisible = true;
    },

    formatDate(dateStr) {
      if (!dateStr) return '';
      
      // 如果是Date对象，转换为字符串
      if (dateStr instanceof Date) {
        const year = dateStr.getFullYear();
        const month = String(dateStr.getMonth() + 1).padStart(2, '0');
        const day = String(dateStr.getDate()).padStart(2, '0');
        return `${year}-${month}-${day}`;
      }
      
      // 如果是字符串，尝试解析并格式化
      if (typeof dateStr === 'string') {
        // 移除可能的时间部分
        const dateOnly = dateStr.split('T')[0].split(' ')[0];
        
        // 检查是否是有效的日期格式
        if (dateOnly.match(/^\d{4}-\d{2}-\d{2}$/)) {
          return dateOnly;
        }
        
        // 尝试解析其他格式的日期
        const date = new Date(dateStr);
        if (!isNaN(date.getTime())) {
          const year = date.getFullYear();
          const month = String(date.getMonth() + 1).padStart(2, '0');
          const day = String(date.getDate()).padStart(2, '0');
          return `${year}-${month}-${day}`;
        }
      }
      
      // 如果无法解析，返回原字符串的前10位（兼容旧数据）
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

.table-selector-container {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 80vh;
}

.tree-management {
  height: 100%;
}

.tree-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
  padding-bottom: 15px;
  border-bottom: 1px solid #e4e7ed;
}

.header-left {
  display: flex;
  align-items: center;
  gap: 15px;
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
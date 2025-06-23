<template>
  <div class="family-tree">
    <h1>家庭族谱</h1>
    <div class="family-member" v-for="member in familyMembers" :key="member.id">
      <div class="member-info">，
        <p><strong>姓名:</strong> {{ member.name }}</p>
        <p><strong>性别:</strong> {{ member.gender }}</p>
        <p><strong>生日:</strong> {{ member.dob }}</p>
        <p><strong>关系:</strong> {{ member.relationship }}</p>
      </div>
      <div class="relationships">
        <h3>关系：</h3>
        <ul>
          <li v-for="relation in member.relations" :key="relation.id">{{ relation.name }} ({{ relation.type }})</li>
        </ul>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      familyMembers: [
        {
          id: 1,
          name: '张三',
          gender: '男',
          dob: '1980-01-01',
          relationship: '父亲',
          relations: [
            { id: 2, name: '李四', type: '妻子' },
            { id: 3, name: '王五', type: '儿子' }
          ]
        },
        {
          id: 2,
          name: '李四',
          gender: '女',
          dob: '1982-02-02',
          relationship: '母亲',
          relations: [
            { id: 1, name: '张三', type: '丈夫' },
            { id: 3, name: '王五', type: '儿子' }
          ]
        },
        {
          id: 3,
          name: '王五',
          gender: '男',
          dob: '2005-05-05',
          relationship: '儿子',
          relations: [
            { id: 1, name: '张三', type: '父亲' },
            { id: 2, name: '李四', type: '母亲' }
          ]
        }
      ]
    };
  }
};
</script>

<style scoped>
.family-tree {
  font-family: Arial, sans-serif;
  padding: 20px;
  background-color: #f5f5f5;
}

h1 {
  text-align: center;
}

.family-member {
  background-color: #fff;
  margin: 10px 0;
  padding: 20px;
  border-radius: 8px;
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
}

.member-info {
  margin-bottom: 10px;
}

.relationships ul {
  list-style-type: none;
  padding-left: 0;
}

.relationships li {
  background-color: #f9f9f9;
  margin: 5px 0;
  padding: 5px;
  border-radius: 5px;
}
</style>
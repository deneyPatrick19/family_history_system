<template>
  <TreeChart :json="treeData" />
</template>

<script>
// 引入 vue-tree-chart
import TreeChart from "vue-tree-chart";
export default {
    components: {
    	TreeChart
    },
    data() {
        return {
            treeData: {
            name: 'root',
            image_url: "https://static.refined-x.com/avat.jpg",
            class: ["rootNode"],
            children: [
            {
              name: 'children1',
              image_url: "https://static.refined-x.com/avat1.jpg"
            },
            {
              name: 'children2',
              image_url: "https://static.refined-x.com/avat2.jpg",
              mate: {
              name: 'mate',
              image_url: "https://static.refined-x.com/avat3.jpg"
            },
            children: [
            {
              name: 'grandchild',
              image_url: "https://static.refined-x.com/avat.jpg"
            },
            {
              name: 'grandchild2',
              image_url: "https://static.refined-x.com/avat1.jpg"
            },
            {
              name: 'grandchild3',
              image_url: "https://static.refined-x.com/avat2.jpg"
            }
          ]
        },
        {
          name: 'children3',
          image_url: "https://static.refined-x.com/avat.jpg"
        }
        ]
        }
        }
      }
    }
</script>

<style scoped>
</style>

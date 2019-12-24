# 概要
「今こそ始めよう！　Kubernetes入門」でKubernetes入門を始めてみる。この掲載は神資料。
- https://thinkit.co.jp/series/7342

minikube.mdを参考にローカルでKubernetesが動かせるようになっている必要がある。

# 詳細

まずは最初にPodが存在しないことを確認する
```
$ kubectl get pods
No resources found.
```

次のPod定義ファイルを用意します。
```
$ cat sample-pod.yml 
# sample-pod.yml
apiVersion: v1
kind: Pod
metadata:
  name: sample-pod
spec:
  containers:
    - name: nginx-container
      image: nginx:1.12
```

podを新規作成します。
```
$ kubectl create -f sample-pod.yml
pod/sample-pod created      
```

Pod の一覧を取得してみます。
```
$ kubectl get pods
NAME         READY   STATUS    RESTARTS   AGE
sample-pod   1/1     Running   0          53s
```


wideを付与すると、Pod の一覧を少しだけ詳細に取得します。
```
$ kubectl get pods -o wide
NAME         READY   STATUS    RESTARTS   AGE   IP           NODE       NOMINATED NODE   READINESS GATES
sample-pod   1/1     Running   0          77s   172.17.0.6   minikube   <none>           <none>
```

なお、kubectl describeコマンドで指定したpodに関する詳細な情報を出力
```
$ kubectl describe pods sample-pod
Name:               sample-pod
Namespace:          default
Priority:           0
PriorityClassName:  <none>
Node:               minikube/192.168.99.101
Start Time:         Wed, 25 Dec 2019 00:29:03 +0900
Labels:             <none>
Annotations:        <none>
Status:             Running
IP:                 172.17.0.6
Containers:
  nginx-container:
    Container ID:   docker://592f79ac399b95fe994322c445717839bcb601f9a86f0170cd091427f7049721
    Image:          nginx:1.12
    Image ID:       docker-pullable://nginx@sha256:72daaf46f11cc753c4eab981cbf869919bd1fee3d2170a2adeac12400f494728
    Port:           <none>
    Host Port:      <none>
    State:          Running
      Started:      Wed, 25 Dec 2019 00:29:18 +0900
    Ready:          True
    Restart Count:  0
    Environment:    <none>
    Mounts:
      /var/run/secrets/kubernetes.io/serviceaccount from default-token-b72cf (ro)
Conditions:
  Type              Status
  Initialized       True 
  Ready             True 
  ContainersReady   True 
  PodScheduled      True 
Volumes:
  default-token-b72cf:
    Type:        Secret (a volume populated by a Secret)
    SecretName:  default-token-b72cf
    Optional:    false
QoS Class:       BestEffort
Node-Selectors:  <none>
Tolerations:     node.kubernetes.io/not-ready:NoExecute for 300s
                 node.kubernetes.io/unreachable:NoExecute for 300s
Events:
  Type    Reason     Age   From               Message
  ----    ------     ----  ----               -------
  Normal  Scheduled  114s  default-scheduler  Successfully assigned default/sample-pod to minikube
  Normal  Pulling    113s  kubelet, minikube  Pulling image "nginx:1.12"
  Normal  Pulled     99s   kubelet, minikube  Successfully pulled image "nginx:1.12"
  Normal  Created    99s   kubelet, minikube  Created container nginx-container
  Normal  Started    99s   kubelet, minikube  Started container nginx-container
```

「kubectl get pods -o wide」 で出力されたnodeに関する値であるminikubeを引数に指定してそのnodeの詳細を確認できます。
Nodeを指定した場合には、リソースの使用状況・空き状況や、起動しているPodのリソース使用率も表示することができます。
```
$ kubectl describe node minikube
Name:               minikube
Roles:              master
Labels:             beta.kubernetes.io/arch=amd64
                    beta.kubernetes.io/os=linux
                    kubernetes.io/arch=amd64
                    kubernetes.io/hostname=minikube
                    kubernetes.io/os=linux
                    node-role.kubernetes.io/master=
Annotations:        kubeadm.alpha.kubernetes.io/cri-socket: /var/run/dockershim.sock
                    node.alpha.kubernetes.io/ttl: 0
                    volumes.kubernetes.io/controller-managed-attach-detach: true
CreationTimestamp:  Tue, 24 Dec 2019 23:42:55 +0900
Taints:             <none>
Unschedulable:      false
Conditions:
  Type             Status  LastHeartbeatTime                 LastTransitionTime                Reason                       Message
  ----             ------  -----------------                 ------------------                ------                       -------
  MemoryPressure   False   Wed, 25 Dec 2019 00:29:29 +0900   Tue, 24 Dec 2019 23:42:50 +0900   KubeletHasSufficientMemory   kubelet has sufficient memory available
  DiskPressure     False   Wed, 25 Dec 2019 00:29:29 +0900   Tue, 24 Dec 2019 23:42:50 +0900   KubeletHasNoDiskPressure     kubelet has no disk pressure
  PIDPressure      False   Wed, 25 Dec 2019 00:29:29 +0900   Tue, 24 Dec 2019 23:42:50 +0900   KubeletHasSufficientPID      kubelet has sufficient PID available
  Ready            True    Wed, 25 Dec 2019 00:29:29 +0900   Tue, 24 Dec 2019 23:43:08 +0900   KubeletReady                 kubelet is posting ready status
Addresses:
  InternalIP:  192.168.99.101
  Hostname:    minikube
Capacity:
 cpu:                2
 ephemeral-storage:  17784772Ki
 hugepages-2Mi:      0
 memory:             1986524Ki
 pods:               110
Allocatable:
 cpu:                2
 ephemeral-storage:  17784772Ki
 hugepages-2Mi:      0
 memory:             1986524Ki
 pods:               110
System Info:
 Machine ID:                 76a489b97f79404095832283b2cf92e1
 System UUID:                b6033127-6ecb-48d1-9837-ac53ae52538c
 Boot ID:                    5a7b1f38-9e0a-4747-b8da-baa95ad45d5b
 Kernel Version:             4.19.81
 OS Image:                   Buildroot 2019.02.7
 Operating System:           linux
 Architecture:               amd64
 Container Runtime Version:  docker://19.3.5
 Kubelet Version:            v1.17.0
 Kube-Proxy Version:         v1.17.0
Non-terminated Pods:         (12 in total)
  Namespace                  Name                                          CPU Requests  CPU Limits  Memory Requests  Memory Limits  AGE
  ---------                  ----                                          ------------  ----------  ---------------  -------------  ---
  default                    sample-pod                                    0 (0%)        0 (0%)      0 (0%)           0 (0%)         3m51s
  kube-system                coredns-6955765f44-m2xjl                      100m (5%)     0 (0%)      70Mi (3%)        170Mi (8%)     49m
  kube-system                coredns-6955765f44-vj8c6                      100m (5%)     0 (0%)      70Mi (3%)        170Mi (8%)     49m
  kube-system                etcd-minikube                                 0 (0%)        0 (0%)      0 (0%)           0 (0%)         49m
  kube-system                kube-addon-manager-minikube                   5m (0%)       0 (0%)      50Mi (2%)        0 (0%)         49m
  kube-system                kube-apiserver-minikube                       250m (12%)    0 (0%)      0 (0%)           0 (0%)         49m
  kube-system                kube-controller-manager-minikube              200m (10%)    0 (0%)      0 (0%)           0 (0%)         49m
  kube-system                kube-proxy-vxl4l                              0 (0%)        0 (0%)      0 (0%)           0 (0%)         49m
  kube-system                kube-scheduler-minikube                       100m (5%)     0 (0%)      0 (0%)           0 (0%)         49m
  kube-system                storage-provisioner                           0 (0%)        0 (0%)      0 (0%)           0 (0%)         49m
  kubernetes-dashboard       dashboard-metrics-scraper-7b64584c5c-h2ddr    0 (0%)        0 (0%)      0 (0%)           0 (0%)         43m
  kubernetes-dashboard       kubernetes-dashboard-79d9cd965-bzdn5          0 (0%)        0 (0%)      0 (0%)           0 (0%)         43m
Allocated resources:
  (Total limits may be over 100 percent, i.e., overcommitted.)
  Resource           Requests    Limits
  --------           --------    ------
  cpu                755m (37%)  0 (0%)
  memory             190Mi (9%)  340Mi (17%)
  ephemeral-storage  0 (0%)      0 (0%)
Events:
  Type    Reason                   Age                From                  Message
  ----    ------                   ----               ----                  -------
  Normal  NodeHasSufficientMemory  50m (x5 over 50m)  kubelet, minikube     Node minikube status is now: NodeHasSufficientMemory
  Normal  NodeHasNoDiskPressure    50m (x4 over 50m)  kubelet, minikube     Node minikube status is now: NodeHasNoDiskPressure
  Normal  NodeHasSufficientPID     50m (x4 over 50m)  kubelet, minikube     Node minikube status is now: NodeHasSufficientPID
  Normal  Starting                 49m                kubelet, minikube     Starting kubelet.
  Normal  NodeHasSufficientMemory  49m                kubelet, minikube     Node minikube status is now: NodeHasSufficientMemory
  Normal  NodeHasNoDiskPressure    49m                kubelet, minikube     Node minikube status is now: NodeHasNoDiskPressure
  Normal  NodeHasSufficientPID     49m                kubelet, minikube     Node minikube status is now: NodeHasSufficientPID
  Normal  NodeAllocatableEnforced  49m                kubelet, minikube     Updated Node Allocatable limit across pods
  Normal  Starting                 49m                kube-proxy, minikube  Starting kube-proxy.
  Normal  NodeReady                49m                kubelet, minikube     Node minikube status is now: NodeReady
```


出力されるPodのログを確認したい場合には次のようにいくつかの方法があります(まだ試せていません)
```
# Pod内のコンテナのログを出力
$ kubectl logs sample-pod

# 複数コンテナが入ったPodで特定のコンテナのログを出力
$ kubectl logs sample-pod -c nginx-container

# followしながらログを出力
$ kubectl logs -f sample-pod

# 最新1時間以内、10件取得、タイムスタンプを表示してログを出力
$ kubectl logs --since=1h --tail=10 --timestamps=true sample-pod
```

続いて、次のDeployment定義ファイルを用意します。
```
$ cat deployment_sample.yml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: sample-deployment
spec:
  replicas: 3
  selector:
    matchLabels:
      app: sample-app
  template:
    metadata:
      labels:
        app: sample-app
    spec:
      containers:
        - name: nginx-container
          image: nginx:1.12
          ports:
            - containerPort: 80
```

recordオプションを付与しておくことでアップデートを行った履歴を保持しておくことが可能になるようです(ロールバック時のリビジョン指定に利用する)。
```
$ kubectl apply -f ./deployment_sample.yml --record
deployment.apps/sample-deployment created
```

上記の適用を行うとReplicaSet(rs)を確認した際に出力されるようになります。
```
$ kubectl get rs 
NAME                          DESIRED   CURRENT   READY   AGE
sample-deployment-c6c6778b4   3         3         3       34s
```


deploymentを見るとほとんどrsと同じような情報を出力していることが確認できます。
```
$ kubectl get deployment
NAME                READY   UP-TO-DATE   AVAILABLE   AGE
sample-deployment   3/3     3            3           66s

$ kubectl get pods
NAME                                READY   STATUS    RESTARTS   AGE
sample-deployment-c6c6778b4-f9cp9   1/1     Running   0          114s
sample-deployment-c6c6778b4-rfqzp   1/1     Running   0          114s
sample-deployment-c6c6778b4-rgw8c   1/1     Running   0          114s
sample-pod                          1/1     Running   0          24m
```

続いて、試しにDeploymentで利用しているコンテナイメージを、nginx:1.12からnginx:1.13にアップデートしてみたいと思います。イメージの更新には「kubectl set image」コマンドを利用します。
```
$ kubectl set image deployment sample-deployment nginx-container=nginx:1.13
deployment.apps/sample-deployment image updated
```


以下のコマンドでpods状況を確認してみると、先ほどまで出力されていた「NAME」を全て置き換えていくような流れになっていることがわかります。
この後、kubectl get podsを実行しても、先ほどまで表示されていたsample-deployment-c6c6778b4-rgw8cについては表示されなくなりました。
```
$ kubectl get pods
NAME                                 READY   STATUS        RESTARTS   AGE
sample-deployment-7cb55c5c99-7hvlt   1/1     Running       0          12s
sample-deployment-7cb55c5c99-dx5gg   1/1     Running       0          22s
sample-deployment-7cb55c5c99-vxmv5   1/1     Running       0          13s
sample-deployment-c6c6778b4-rgw8c    0/1     Terminating   0          3m25s
sample-pod                           1/1     Running       0          25m
```


続いて、ロールバックをしたい場合には、履歴を以下のコマンドで確認することができます。
```
$  kubectl rollout history deployment sample-deployment
deployment.apps/sample-deployment 
REVISION  CHANGE-CAUSE
1         kubectl apply --filename=./deployment_sample.yml --record=true
2         kubectl apply --filename=./deployment_sample.yml --record=true
```

次のようにして、ロールバックするリビジョンを指定することができます。(未実行)
```
# 1つ前にロールバックする場合（デフォルトの--to-revision 0が指定される）
$ kubectl rollout undo deployment sample-deployment
deployment "sample-deployment" rolled back

# リビジョンを指定してロールバックする場合
$ kubectl rollout undo deployment sample-deployment --to-revision 1
deployment "sample-deployment" rolled back
```

(とりあえず第３回ぐらいまでまとめているので、引き続きまとめたい)

# 参考URL
- 今こそ始めよう！　Kubernetes入門
  - https://thinkit.co.jp/series/7342
- 青山さんスライド
  - https://speakerdeck.com/masayaaoyama/devsumi2019-amsy810-k8s


# Official
- Kubernetes公式ドキュメント
  - https://kubernetes.io/docs/home/
- bootcamp
  - https://kubernetesbootcamp.github.io/kubernetes-bootcamp/index.html



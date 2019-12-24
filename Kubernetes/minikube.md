# 概要
minikubeとはKubernetesをローカル環境で動かす仕組みです。

自分はMACでminikubeを利用してに関するインストールを行い、VirtualBoxと連携してminikubeのクイックスタートの実施をしています。
また、minikubeに関するコマンドなどもまとめています。

基本的にはminikubeインストール方法は以下に従います。
- https://kubernetes.io/docs/tasks/tools/install-minikube/#before-you-begin

インストール完了後は以下のドキュメントに従って簡単なサンプルを試してみます。
- https://kubernetes.io/docs/setup/learning-environment/minikube/

# 詳細

### インストール(MAC)
ドキュメントに記載されている通り以下のコマンドを実行します。
```
$ brew install minikube
$ curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-darwin-amd64 \
  && chmod +x minikube
$ sudo mv minikube /usr/local/bin
```

### QuickStartを実行してみる
vm-driverにはvirtualboxを指定します。
```
$ minikube start --vm-driver=virtualbox
😄  minikube v1.6.2 on Darwin 10.14.5
✨  Selecting 'virtualbox' driver from user configuration (alternates: [hyperkit])
💿  Downloading VM boot image ...
    > minikube-v1.6.0.iso.sha256: 65 B / 65 B [--------------] 100.00% ? p/s 0s
    > minikube-v1.6.0.iso: 150.93 MiB / 150.93 MiB [-] 100.00% 5.34 MiB p/s 29s
🔥  Creating virtualbox VM (CPUs=2, Memory=2000MB, Disk=20000MB) ...
🐳  Preparing Kubernetes v1.17.0 on Docker '19.03.5' ...
💾  Downloading kubeadm v1.17.0
💾  Downloading kubelet v1.17.0
🚜  Pulling images ...
🚀  Launching Kubernetes ... 
⌛  Waiting for cluster to come online ...
🏄  Done! kubectl is now configured to use "minikube"
⚠️  /usr/local/bin/kubectl is version 1.14.8, and is incompatible with Kubernetes 1.17.0. You will need to update /usr/local/bin/kubectl or use 'minikube kubectl' to connect with this cluster
```

インストールが完了したら次のコマンドでクラスタのステータスを確認できるようです。
```
$ minikube status
host: Running
kubelet: Running
apiserver: Running
kubeconfig: Configured
```

続いて、こちらのサンプルを試してみます。
- https://kubernetes.io/docs/setup/learning-environment/minikube/

echoserverのイメージ(k8s.gcr.io/echoserver:1.10)があるのでそれを利用して、deploymentを定義します。名前はhello-minikubeとします。
```
$ kubectl create deployment hello-minikube --image=k8s.gcr.io/echoserver:1.10
deployment.apps/hello-minikube created
```

以下のコマンドで8080ポートとしてServiceとして提供します。先ほどのdeploymentで定義したhello-minikubeを指定しています。
```
$ kubectl expose deployment hello-minikube --type=NodePort --port=8080
service/hello-minikube exposed
```

Podの状態を確認します。
```
$ kubectl get pod
NAME                              READY   STATUS    RESTARTS   AGE
hello-minikube-797f975945-4lbtc   1/1     Running   0          74s
```

作成したサービスのURLを確認するには次のコマンドで確認できます。
```
$ minikube service hello-minikube --url
http://192.168.99.100:30161
```

上記URLにアクセスしてみるとechoserverとして次のような出力が表示されます。
```
Hostname: hello-minikube-797f975945-4lbtc

Pod Information:
	-no pod information available-

Server values:
	server_version=nginx: 1.13.3 - lua: 10008

Request Information:
	client_address=172.17.0.1
	method=GET
	real path=/
	query=
	request_version=1.1
	request_scheme=http
	request_uri=http://192.168.99.100:8080/

Request Headers:
	accept=text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
	accept-encoding=gzip, deflate
	accept-language=ja,en-US;q=0.9,en;q=0.8
	connection=keep-alive
	host=192.168.99.100:30161
	upgrade-insecure-requests=1
	user-agent=Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.79 Safari/537.36

Request Body:
	-no body in request-
```

hello-minikubeのService定義とDeployment定義を削除します。
```
$ kubectl delete services hello-minikube
service "hello-minikube" deleted

$ kubectl delete deployment hello-minikube
deployment.apps "hello-minikube" deleted
```

minikubeを定義するには次のコマンドを実行します。
これを実行するとVirtualBox上の画面でminikubeは「停止中」とステータスが変化します。
```
$ minikube stop
✋  Stopping "minikube" in virtualbox ...
🛑  "minikube" stopped.
```

以下のコマンドを実行するとVirtualBox上のminikubeを削除します。これは残したままでもいいかもしれません。
```
$ minikube delete
🔥  Deleting "minikube" in virtualbox ...
💔  The "minikube" cluster has been deleted.
🔥  Successfully deleted profile "minikube"
```

以上で、QuickStartのチュートリアルは終了です。

### ダッシュボードを表示する
以下のコマンドを実行すると、ブラウザにリダイレクトされて専用のダッシュボード画面が表示されます。
```
$ minikube dashboard
🔌  Enabling dashboard ...
🤔  Verifying dashboard health ...
🚀  Launching proxy ...
🤔  Verifying proxy health ...
🎉  Opening http://127.0.0.1:49262/api/v1/namespaces/kubernetes-dashboard/services/http:kubernetes-dashboard:/proxy/ in your default browser...
```

### クラスタ情報を取得する
```
$ kubectl cluster-info
Kubernetes master is running at https://192.168.99.101:8443
KubeDNS is running at https://192.168.99.101:8443/api/v1/namespaces/kube-system/services/kube-dns:dns/proxy

To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
```

### 提供しているサービス情報を取得する 
```
$ minikube service list
|----------------------|---------------------------|--------------|-----|
|      NAMESPACE       |           NAME            | TARGET PORT  | URL |
|----------------------|---------------------------|--------------|-----|
| default              | kubernetes                | No node port |
| kube-system          | kube-dns                  | No node port |
| kubernetes-dashboard | dashboard-metrics-scraper | No node port |
| kubernetes-dashboard | kubernetes-dashboard      | No node port |
|----------------------|---------------------------|--------------|-----|
```


### ノード情報を取得する
```
$ kubectl get nodes
NAME       STATUS   ROLES    AGE   VERSION
minikube   Ready    master   13m   v1.17.0
```


### サポートしているaddonのリストを表示する
```
 minikube addons list
- addon-manager: enabled
- dashboard: enabled
- default-storageclass: enabled
- efk: disabled
- freshpod: disabled
- gvisor: disabled
- helm-tiller: disabled
- ingress: disabled
- ingress-dns: disabled
- logviewer: disabled
- metrics-server: disabled
- nvidia-driver-installer: disabled
- nvidia-gpu-device-plugin: disabled
- registry: disabled
- registry-creds: disabled
- storage-provisioner: enabled
- storage-provisioner-gluster: disabled
```


# Informative URL
- Install Minikube
  - https://kubernetes.io/docs/tasks/tools/install-minikube/#before-you-begin
- Installing Kubernetes with Minikube
  - https://kubernetes.io/docs/setup/learning-environment/minikube/

# Official URL
- minikube公式ドキュメント
  - https://minikube.sigs.k8s.io/docs/
- ソースコード
  - https://github.com/kubernetes/minikube


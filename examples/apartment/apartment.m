% 
function apartment
clear set
close all
figure
hold on

addpath(genpath('/home/baiyunjun/Documents/online_algorithm/mfiles/'))
% plot the vehicle domain
% colors
colors=get(groot,'DefaultAxesColorOrder');

% load the symbolic set containig obstacles
obs=GridPoints('obstacles');
obs=unique(obs(:,[1 2]),'rows');
plot(obs(:,1),obs(:,2),'.');
hold on

target=GridPoints('target');
target=unique(target(:,[1 2]),'rows');
plot(target(:,1),target(:,2),'.','color',colors(2,:));
hold on

% re_lazy=GridPoints('recomputation_lazy');
% re_lazy=unique(re_lazy(:,[1,2]),'rows');
% plot(re_lazy(:,1),re_lazy(:,2),'.','color',colors(2,:));

winDomain=StaticController('controller_scots2');
domain=winDomain.domain;
 for i=1:size(domain,1)
     x=domain(i,1)-0.1;
     y=domain(i,2)-0.1;
     rectangle('Position',[x y 0.2 0.2], 'FaceColor','green','EdgeColor','green');
 end

winDomain_scots=StaticController('controller_global');
domain_scots=winDomain_scots.domain;
for k=1:size(domain_scots,1)
    x=domain_scots(k,1)-0.1;
    y=domain_scots(k,2)-0.1;
    %rectangle('Position',[x y 0.2 0.2],'FaceColor','red','EdgeColor','red');
    rectangle('Position',[x y 0.2 0.2]);
end

% plot the real obstacles and target set
plot_domain

box on
axis([0 10 0 6])

%set(gcf,'paperunits','centimeters','paperposition',[0 0 16 10],'papersize',[16 6])

end



function plot_domain

colors=get(groot,'DefaultAxesColorOrder');


alpha=0.2;

v=[7.6 0;10 0;7.6 1.8; 10 1.8];
patch('vertices',v,'faces',[1 2 4 3],'facea', alpha ,'edgec',colors(2,:));
v=[4.2 0;7.4 0;4.2 1.8; 7.4 1.8];
patch('vertices',v,'faces',[1 2 4 3],'facea', alpha, 'facec',colors(3,:));

v=[9 0; 9.5  0; 9 0.5; 9.5 .5];
patch('vertices',v,'faces',[1 2 4 3],'facea',alpha,'facec',colors(2,:),'edgec',colors(2,:));


v=[4.0     0  ;4.2  0 ; 4.0  2 ; 4.2  2  ];
patch('vertices',v,'faces',[1 2 4 3],'facea',alpha,'facec',colors(1,:),'edgec',colors(1,:));
v=[5     1.8;7.6  1.8   ; 5   2.0    ; 7.6 2.0   ];
patch('vertices',v,'faces',[1 2 4 3],'facea',alpha,'facec',colors(1,:),'edgec',colors(1,:));
v=[4.0 3.4; 4.2 3.4; 4.0 6; 4.2 6];
patch('vertices',v,'faces',[1 2 4 3],'facea',alpha,'facec',colors(1,:),'edgec',colors(1,:));
v=[5 3.4; 7.6 3.4; 5 3.6; 7.6 3.6];
patch('vertices',v,'faces',[1 2 4 3],'facea',alpha,'facec',colors(1,:),'edgec',colors(1,:));
v=[7.4   0  ;7.6  0   ; 7.4   2.0   ; 7.6 2.0  ];
patch('vertices',v,'faces',[1 2 4 3],'facea',alpha,'facec',colors(1,:),'edgec',colors(1,:));
v=[7.4   3.4  ;7.6  3.4   ; 7.4   6.0    ; 7.6  6.0   ];
patch('vertices',v,'faces',[1 2 4 3],'facea',alpha,'facec',colors(1,:),'edgec',colors(1,:));
v=[8.4  1.8  ;10.0  1.8   ;8.4  2.0   ; 10.0  2.0  ];
patch('vertices',v,'faces',[1 2 4 3],'facea',alpha,'facec',colors(1,:),'edgec',colors(1,:));
v=[8.4   3.4  ;10.0    3.4   ; 8.4   3.6    ; 10.0   3.6   ];
patch('vertices',v,'faces',[1 2 4 3],'facea',alpha,'facec',colors(1,:),'edgec',colors(1,:));

end

